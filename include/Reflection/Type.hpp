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
#include <Reflection/Main.hpp>
namespace Reflection{
    class Type{
        public:
            bool const_, volatile_, restrict_;
            virtual std::size_t size() const=0;
            virtual ~Type() noexcept;
    };
    class BaseType: public Type{
        public:
            virtual std::size_t size() const;
    };
    class PointerType: public Type{
        public:
            Type *to;
            virtual std::size_t size() const;
    };
    class PointerToMemberType: public Type{
        public:
            Class *of;
            Type *to;
            virtual std::size_t size() const;
    };
    class PointerToFunctionType: public Type{
        public:
            Type *return_;
            std::vector<Type*> parameters;
            virtual std::size_t size() const;
    };
    class PointerToMemberFunctionType: public Type{
        public:
            Class *of;
            Type *return_;
            std::vector<Type*> parameters;
            virtual std::size_t size() const;
    };
    class Enumerator: public Declared{
        public:
            std::string name;
            long long value;
    };
    class Enum: public Type, public Declared, public Scope{
        public:
            bool isEnumClass;
            virtual std::size_t size() const;
            // May be in:
            //     Class
            //     Namespace
            //     Function
            // May contain:
            //     Enumerator
    };
    class Array: public Type{
        public:
            Type *of;
            std::vector<std::size_t> sizes;
            virtual std::size_t size() const;
    };
}
