/*
 * Copyright (C) 2015 Niek Linnenbank
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

#include <Types.h>
#include <Macros.h>
#include <stdio.h>
#include <unistd.h>
#include <ProcessClient.h>
#include "Renice.h"

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("");
    parser().registerFlag('n', "new", "Priority to be used with scheduled process");
    parser().registerPositional("PRIORITY", "Priority level for process");
    parser().registerPositional("PROCESSID", "Processes ID for process");

}

Renice::~Renice(){}

Renice::Result Renice::exec()
{
    if(arguments().get("new")){

        ProcessClient process;
        int priority = atoi(arguments().get("PRIORITY"));
        ProcessID pid = atoi(arguments().get("PROCESSID"));

        if (priority > 5 || priority < 1) {
            return InvalidArgument;
        }

        process.setPriorty(pid, priority)

        return Success;
    }

    return InvalidArgument;
}

