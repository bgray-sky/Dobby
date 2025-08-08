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

#ifndef ETHANLOGSYSLOGMESSAGE_H
#define ETHANLOGSYSLOGMESSAGE_H

#include <string>

class EthanLogSyslogMessage // : public EthanLogMessage
{
public:
    EthanLogSyslogMessage();

    int processIdentifier(const char *field, ssize_t len);
    int processLogLevel(const char *field, ssize_t len);
    int processPid(pid_t pid);
    int processTimestamp(const char *field, ssize_t len);
    int processThreadName(const char *field, ssize_t len);
    int processCodeFile(const char *field, ssize_t len);
    int processCodeFunction(const char *field, ssize_t len);
    int processCodeLine(const char *field, ssize_t len);
    int processMessage(const char *field, ssize_t len);

    void emit();

    void clear();

    void dump();

private:
    int mPriority;
    std::string mMessage;
};

#endif //ETHANLOGSYSLOGMESSAGE_H
