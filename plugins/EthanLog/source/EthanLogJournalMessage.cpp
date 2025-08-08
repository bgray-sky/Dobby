/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2016 Sky UK
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

#include "EthanLogJournalMessage.h"

#include <Logging.h>

#define SD_JOURNAL_SUPPRESS_LOCATION

#include <systemd/sd-event.h>
#include <systemd/sd-journal.h>


#define ETHANLOG_MAX_LOG_MSG_LENGTH       512UL


void EthanLogJournalMessage::clear()
{
    mFields = 0;
}

void EthanLogJournalMessage::emit()
{
    if (mFields < 2)
        return;

    int rc = sd_journal_sendv(mFields, mNumFields);
    if (rc < 0)
        AI_LOG_SYS_ERROR(-rc, "failed to write to journald");
}

int EthanLogJournalMessage::processIdentifier(const char *field, ssize_t len)
{
    if (mFields >= mMaxFields)
        return -1;

    static char buf[18 + ETHANLOG_MAX_IDENTIFIER];
    memcpy(buf, "SYSLOG_IDENTIFIER=", 18);

    len = std::min<size_t>(ETHANLOG_MAX_IDENTIFIER, len);
    memcpy(buf + 18, field, len);

    mFields[mFields].iov_base = const_cast<char*>(buf);
    mFields[mFields].iov_len = 18 + len;
    mFields++;

    return 0;
}

int processLogLevel(const char *field, ssize_t len);
int EthanLogJournalMessage::processPid(pid_t pid)
{
    if (mFields >= (mMaxFields - 1))
        return -1;

    {
        static char syslogBuf[48];
        mFields[mFields].iov_base = syslogBuf;
        mFields[mFields].iov_len = sprintf(syslogBuf, "SYSLOG_PID=%ld", pid);
        mFields++;
    }

    {
        static char objBuf[48];
        mFields[mFields].iov_base = objBuf;
        mFields[mFields].iov_len = sprintf(objBuf, "OBJECT_PID=%ld", pid);
        mFields++;
    }

    return 0;
}

int processTimestamp(const char *field, ssize_t len);
int processThreadName(const char *field, ssize_t len);
int processCodeFile(const char *field, ssize_t len);
int processCodeFunction(const char *field, ssize_t len);
int processCodeLine(const char *field, ssize_t len);

int EthanLogJournalMessage::processMessage(const char *field, ssize_t len)
{
    if (mFields >= mMaxFields)
        return -1;

    static char buf[8 + ETHANLOG_MAX_LOG_MSG_LENGTH];
    memcpy(buf, "MESSAGE=", 8);

    len = std::min<size_t>(ETHANLOG_MAX_LOG_MSG_LENGTH, len);
    memcpy(buf + 8, field, len);

    mFields[mFields].iov_base = buf;
    mFields[mFields].iov_len = 8 + len;
    mFields++;

    return 0;
}


