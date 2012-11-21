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
    class Function: public Declared, public Scope{
        public:
            class Parameter: public Declared{
                public:
                    std::string name;
                    Type *type;
                    // May be in:
                    //     Function
            };
            std::string name;
            CodePointer begin, end;
            Type *return_;
            std::vector<Parameter*> parameters;
            std::vector<TemplateArgument*> templateArguments;
            virtual ~Function() noexcept;
            // May be in:
            //     Namespace
            //     Class
            // May contain:
            //     Parameter
            //     Class
            //     Enum
    };
    class MemberFunction: public Function{
         public:
             Class *memberOf;
             bool const_, volatile_, static_;
    };
}
