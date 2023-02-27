/*
 * Copyright (C) 2009 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Wait.h"
#include "POSIXApplication.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for a process with the given PID to terminate");
    parser().registerPositional("PID", "The PID of the process to wait for");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    int pid_ = atoi(arguments().get("PID"));

    if (pid_ <= 0)
    {
        ERROR("invalid PID: " << arguments().get("PID"));
        return InvalidArgument;
    }

    // Wait now
    if (waitpid(pid_, &pid_, 0) == -1)
    {
        ERROR("failed to wait for PID: " << pid_ << ":" << strerror(errno));
        return IOError;
    }
    
    INFO("Process " << pid_ << " has terminated.");

    // Done
    return Success;
}
