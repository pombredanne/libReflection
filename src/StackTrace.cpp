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
#include <Reflection/StackTrace.hpp>
#include <cstdlib>
#include <execinfo.h>
namespace Reflection{
    StackTrace::StackTrace(size_t N, size_t skip):
    alloc_(reinterpret_cast<void**>(std::malloc(sizeof(CodePointer)*(N+skip)))),
    begin_(alloc_+skip+1),end_(alloc_+backtrace(alloc_, N)){
        return;
    }
    StackTrace::StackTrace(const StackTrace &that):
    alloc_(reinterpret_cast<void**>(std::malloc(sizeof(CodePointer)*that.size()))),
    begin_(alloc_),end_(std::copy(that.begin_, that.end_, begin_)){
        return;
    }
    StackTrace::StackTrace(StackTrace &&that):
    alloc_(that.alloc_),
    begin_(that.begin_),
    end_(that.end_){
        that.alloc_=nullptr;
        that.begin_=nullptr;
        that.end_=nullptr;
        return;
    }
    StackTrace &StackTrace::operator=(const StackTrace &that){
        free(alloc_);
        begin_=reinterpret_cast<void**>(std::malloc(sizeof(CodePointer)*that.size()));
        end_=std::copy(that.begin_, that.end_, begin_);
        return *this;
    }
    StackTrace &StackTrace::operator=(StackTrace &&that){
        alloc_=that.alloc_;
        begin_=that.begin_;
        end_=that.end_;
        that.alloc_=nullptr;
        that.begin_=nullptr;
        that.end_=nullptr;
        return *this;
    }
    StackTrace::~StackTrace(){
        free(alloc_);
        return;
    }
}
