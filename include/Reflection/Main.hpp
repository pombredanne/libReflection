/*
    Copyright (C) 2012  Hristo Venev

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#include <string>
#include <vector>
namespace Reflection{
    class ReflectionError;
    class Class;
    class Enum;
    class Type;
    class BaseType;
    class TemplateArgument;
    class Namespace;
    class GlobalVariable;
    class Function;
    class Scope;
    class Declared;
    class StackFrame;
    class StackTrace;
    using CodePointer=void*;
    class Scope{
        public:
            std::vector<Declared*> contents; // contents[*]->location==this
            Declared *byName(const std::string &name);
    };
    class Declared{
        public:
            std::string name;
            Scope *location;
    };
}
