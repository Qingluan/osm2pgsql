#ifndef OSMIUM_RELATIONS_DETAIL_MEMBER_META_HPP
#define OSMIUM_RELATIONS_DETAIL_MEMBER_META_HPP

/*

This file is part of Osmium (http://osmcode.org/libosmium).

Copyright 2013-2016 Jochen Topf <jochen@topf.org> and others (see README).

Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#include <algorithm>
#include <cstddef>
#include <iosfwd>
#include <iterator>

#include <osmium/osm/types.hpp>

namespace osmium {

    namespace relations {

        /**
         * Helper class for the Collector class.
         *
         * Stores an object ID and information where the object should be
         * stored.
         */
        class MemberMeta {

            /**
             * Object ID of this relation member. Can be a node, way, or relation ID.
             * It depends on the vector in which this object is stored which kind of
             * object is referenced here.
             */
            osmium::object_id_type m_member_id;

            /**
             * Position of the relation this member is a part of in the
             * m_relations vector.
             */
            size_t m_relation_pos;

            /**
             * Position of this member in the list of members of the
             * relation this member is a part of.
             */
            size_t m_member_pos;

            /**
             * Offset in the buffer where the object is stored.
             */
            size_t m_buffer_offset { 0 };

            bool m_removed = false;

        public:

            /**
             * Create new MemberMeta. The variant with zeros for relation_pos and
             * member_pos is used to create dummy MemberMeta that can be compared
             * to the MemberMeta in the vectors using the equal_range algorithm.
             */
            explicit MemberMeta(osmium::object_id_type member_id, size_t relation_pos=0, size_t member_pos=0) noexcept :
                m_member_id(member_id),
                m_relation_pos(relation_pos),
                m_member_pos(member_pos) {
            }

            osmium::object_id_type member_id() const noexcept {
                return m_member_id;
            }

            size_t relation_pos() const noexcept {
                return m_relation_pos;
            }

            size_t member_pos() const noexcept {
                return m_member_pos;
            }

            size_t buffer_offset() const noexcept {
                return m_buffer_offset;
            }

            void set_buffer_offset(size_t offset) noexcept {
                m_buffer_offset = offset;
            }

            bool removed() const noexcept {
                return m_removed;
            }

            void remove() noexcept {
                m_removed = true;
            }

        }; // class MemberMeta

        /**
         * Compares two MemberMeta objects by only looking at the member id.
         * Used to sort a vector of MemberMeta objects and to later find
         * them using binary search.
         */
        inline bool operator<(const MemberMeta& a, const MemberMeta& b) noexcept {
            return a.member_id() < b.member_id();
        }

        template <typename TChar, typename TTraits>
        inline std::basic_ostream<TChar, TTraits>& operator<<(std::basic_ostream<TChar, TTraits>& out, const MemberMeta& mm) {
            out << "MemberMeta(member_id=" << mm.member_id() << " relation_pos=" << mm.relation_pos() << " member_pos=" << mm.member_pos() << " buffer_offset=" << mm.buffer_offset() << ")";
            return out;
        }

    } // namespace relations

} // namespace osmium

#endif // OSMIUM_RELATIONS_DETAIL_MEMBER_META_HPP