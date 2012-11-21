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
#include <nstd/iterator.hpp>
namespace Reflection{
    class StackTrace{
        struct IteratorBase{
            CodePointer *ptr;
            public:
                constexpr IteratorBase(CodePointer *p):ptr(p){}
                CodePointer &dereference() const{
                    return *ptr;
                }
                void increment(){
                    ptr++;
                    return;
                }
                void decrement(){
                    ptr--;
                    return;
                }
                void advance(std::ptrdiff_t x){
                    ptr+=x;
                    return;
                }
        };
        public:
            using value_type=CodePointer;
            using reference_type=CodePointer&;
            using const_reference_type=const CodePointer&;
            using pointer_type=CodePointer*;
            using const_pointer_type=const CodePointer*;
            using size_type=std::size_t;
            using difference_type=std::ptrdiff_t;
            using iterator=nstd::iterator_adapter<IteratorBase, value_type, std::random_access_iterator_tag, reference_type, difference_type>;
            using const_iterator=nstd::iterator_adapter<IteratorBase, value_type, std::random_access_iterator_tag, const_reference_type, difference_type>;
            StackTrace(size_t N);
            StackTrace(const StackTrace &that);
            StackTrace(StackTrace &&that);
            StackTrace &operator=(const StackTrace &that);
            StackTrace &operator=(StackTrace &&that);
            ~StackTrace();
            iterator begin(){
                return IteratorBase(begin_);
            }
            iterator end(){
                return IteratorBase(end_);
            }
            const_iterator begin() const{
                return IteratorBase(begin_);
            }
            const_iterator end() const{
                return IteratorBase(end_);
            }
            inline size_type size() const{
                return end_-begin_;
            }
            inline value_type operator[](size_t i){
                return begin_[i];
            }
            inline bool empty() const{
                return begin_==end_;
            }
            inline void swap(StackTrace &that){
                std::swap(begin_, that.begin_);
                std::swap(end_, that.end_);
                return;
            }
        private:
            pointer_type begin_, end_;
    };
}
