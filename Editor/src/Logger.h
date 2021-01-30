#ifndef LOGGER_H
#define LOGGER_H

#include "imgui.h"

// Code from the Imgui example
class Logger
{
public:
    Logger();

    void Clear();

    void AddLog(const char* fmt, ...) IM_FMTARGS(2)
    {
        int old_size = Buf.size();
        va_list args;
        va_start(args, fmt);
        Buf.appendfv(fmt, args);
        va_end(args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n')
                LineOffsets.push_back(old_size + 1);
    }

    void Draw(const char* title, bool* p_open = nullptr);

private:
    ImGuiTextBuffer Buf;
    ImGuiTextFilter Filter;
    ImVector<int> LineOffsets;
    bool AutoScroll;
};

#endif