/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2025 Sky UK
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "EthanLogSyslogMessage.h"

#include <syslog.h>

EthanLogSyslogMessage::EthanLogSyslogMessage()
    : mPriority(LOG_INFO)
{
}

int EthanLogSyslogMessage::processIdentifier(const char *field, ssize_t len)
{
    return 1;
}

int EthanLogSyslogMessage::processLogLevel(const char *field, ssize_t len)
{
    return 1;
}

int EthanLogSyslogMessage::processPid(pid_t pid)
{
    return 1;
}

int EthanLogSyslogMessage::processTimestamp(const char *field, ssize_t len)
{
    return 1;
}

int EthanLogSyslogMessage::processThreadName(const char *field, ssize_t len)
{
    return 1;
}

int EthanLogSyslogMessage::processCodeFile(const char *field, ssize_t len)
{
    return 1;
}

int EthanLogSyslogMessage::processCodeFunction(const char *field, ssize_t len)
{
    return 1;
}

int EthanLogSyslogMessage::processCodeLine(const char *field, ssize_t len)
{
    return 1;
}

int EthanLogSyslogMessage::processMessage(const char *field, ssize_t len)
{
    mMessage.assign(field, len);
    return 1;
}

void EthanLogSyslogMessage::emit()
{
    if (!mMessage.empty())
    {
        syslog(mPriority, "%s", mMessage.c_str());
    }
}

void EthanLogSyslogMessage::clear()
{
    mMessage.clear();
}

void EthanLogSyslogMessage::dump()
{
}
