/*
 *
 * Copyright (C) 2001-2005 Ichiro Fujinaga, Michael Droettboom, Karl MacMillan
 *               2012      Christoph Dalitz
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef kwm11162001_dimensions_hpp
#define kwm11162001_dimensions_hpp

#include <vector>
#include <iostream>

/*
 * This file contains the basic geometric types for Gamera. On one hand it is
 * absolutely silly that we have to implement these types of objects instead
 * of using something from the C++ 'standard'. On the other hand, some of these
 * have methods that are somewhat specific to document recognition.
 */

namespace Gamera {
	
	/**
	 * The basic type used for all coordinates. An unsigned type is used - this can
	 * be inconvenient at times, but it makes interaction with the image processing
	 * layer a little easier.
	 */
	typedef size_t coord_t;
	
	/**
	 * Point
	 *
	 * This is a simple class to hold a single coordinate on a plane (x/y value pair).
	 */
	class Point {
	private:
		coord_t m_x, m_y;
	public:
		/**
		 * Default constructor - x and y are 0
		 */
		Point() : m_x(0), m_y(0) {}
		
		/**
		 * Construct a point for the given x and y coordinates.
		 */
		Point(coord_t x, coord_t y) : m_x(x), m_y(y) {}
		
		/// Return the x coordinate.
		coord_t x() const {
			return m_x;
		}
		
		/// Return the y coordinate.
		coord_t y() const {
			return m_y;
		}
		
		/// Set the x coordinate.
		void x(coord_t x) {
			m_x = x;
		}
		
		/// Set the y coordinate.
		void y(coord_t y) {
			m_y = y;
		}
		
		/// Move this point by the coordinates x and y (i.e. add (x,y))
		void move(int x, int y) {
			m_x += x;
			m_y += y;
		}
		
		/// Equality operator
		bool operator==(const Point &x) const {
			return (m_x == x.m_x && m_y == x.m_y);
		}
		
		/// Inequality operator
		bool operator!=(const Point &x) const {
			return (m_x != x.m_x || m_y != x.m_y);
		}
		
		/// Less Than operator
		/// (this does not make real sense, but allows Points to be keys in Maps)
		bool operator<(const Point &x) const {
			if (m_x < x.m_x) return true;
			if (m_y < x.m_y) return true;
			return false;
		}
		
		/// Gt Than operator
		bool operator>(const Point &x) const {
			if (m_x > x.m_x) return true;
			if (m_x == x.m_x && m_y > x.m_y) return true;
			return false;
		}
		
		/// Addition
		const Point operator+(const Point &p) const {
			return Point(m_x + p.m_x, m_y + p.m_y);
		}
		
		Point operator+=(const Point &p) {
			m_x += p.m_x;
			m_y += p.m_y;
			return *this;
		}
		
	};
	
	/*
	 * There are size _and_ dimension objects so that users can use
	 * whichever coordinate system is most natural.
	 *
	 * A single point Point(0,0) and Size(0, 0) or Dimensions(1, 1)
	 */
	
	/*
	 * Size
	 *
	 * A simple class that holds width and height. These dimensions are
	 * refer to nrows - 1 or ncols - 1.
	 */
	class Size {
	private:
		coord_t m_width, m_height;
	public:
		/// Default constructor - set width and height to 0
		Size() : m_width(1), m_height(1) {}
		
		/// Construct a size object from width and height.
		Size(coord_t width, coord_t height) : m_width(width), m_height(height) {}
		
		/// Return the width
		coord_t width() const {
			return m_width;
		}
		
		/// Return the height
		coord_t height() const {
			return m_height;
		}
		
		/// Set the width
		void width(coord_t width) {
			m_width = width;
		}
		
		/// Set the height
		void height(coord_t height) {
			m_height = height;
		}
		
		/// Equality operator
		bool operator==(const Size &other) const {
			if (m_width == other.width() && m_height == other.height())
				return true;
			else
				return false;
		}
		
		bool operator<(const Size &rhs) const {
			if (m_width < rhs.m_width)
				return true;
			if (rhs.m_width < m_width)
				return false;
			return m_height < rhs.m_height;
		}
		
		bool operator>(const Size &rhs) const {
			return rhs < *this;
		}
		
		bool operator<=(const Size &rhs) const {
			return !(rhs < *this);
		}
		
		bool operator>=(const Size &rhs) const {
			return !(*this < rhs);
		}
		
		/// Inequality operator
		bool operator!=(const Size &other) const {
			if (m_width != other.width() || m_height != other.height())
				return true;
			else
				return false;
		}
	};
	
	/*
	 * Dim
	 *
	 * A simple class that holds nrows and ncols. These dimensions are
	 * refer to width or height + 1.
	 */
	class Dim {
	private:
		coord_t m_ncols, m_nrows;
	public:
		Dim() : m_ncols(1), m_nrows(1) {}
		
		Dim(coord_t cols, coord_t rows) : m_ncols(cols), m_nrows(rows) {}
		
		coord_t ncols() const { return m_ncols; }
		
		coord_t nrows() const { return m_nrows; }
		
		void ncols(coord_t ncols) { m_ncols = ncols; }
		
		void nrows(coord_t nrows) { m_nrows = nrows; }
		
		template<class Other>
		bool operator==(const Other &other) const {
			if (m_ncols == other.ncols() && m_nrows == other.nrows())
				return true;
			else
				return false;
		}
		
		template<class Other>
		bool operator!=(const Other &other) const {
			if (m_ncols != other.ncols() || m_nrows != other.nrows())
				return true;
			else
				return false;
		}
		
		bool operator<(const Dim &rhs) const {
			if (m_ncols < rhs.m_ncols)
				return true;
			if (rhs.m_ncols < m_ncols)
				return false;
			return m_nrows < rhs.m_nrows;
		}
		
		bool operator>(const Dim &rhs) const {
			return rhs < *this;
		}
		
		bool operator<=(const Dim &rhs) const {
			return !(rhs < *this);
		}
		
		bool operator>=(const Dim &rhs) const {
			return !(*this < rhs);
		}
	};
	
	/*
	 * Rect
	 *
	 * A rectangle class
	 */
	
	class Rect {
	public:
		
		Rect() : m_origin(0, 0), m_lr(1, 1) {}
		
		Rect(const Point &upper_left, const Point &lower_right)
				: m_origin(upper_left), m_lr(lower_right) {}
		
		Rect(const Point &upper_left, const Size &size)
				: m_origin(upper_left), m_lr(upper_left.x() + size.width(),
				                             upper_left.y() + size.height()) {}
		
		Rect(const Point &upper_left, const Dim &dim)
				: m_origin(upper_left), m_lr(upper_left.x() + dim.ncols() - 1,
				                             upper_left.y() + dim.nrows() - 1) {}
		
		virtual ~Rect() {}
		
		// Get
		Point origin() const { return m_origin; }
		
		Point ul() const { return m_origin; }
		
		coord_t ul_x() const { return m_origin.x(); }
		
		coord_t ul_y() const { return m_origin.y(); }
		
		Point ur() const { return {m_lr.x(), m_origin.y()}; }
		
		coord_t ur_x() const { return m_lr.x(); }
		
		coord_t ur_y() const { return m_origin.y(); }
		
		Point lr() const { return m_lr; }
		
		coord_t lr_x() const { return m_lr.x(); }
		
		coord_t lr_y() const { return m_lr.y(); }
		
		Point ll() const { return {m_origin.x(), m_lr.y()}; }
		
		coord_t ll_x() const { return m_origin.x(); }
		
		coord_t ll_y() const { return m_lr.y(); }
		
		Dim dim() const { return {ncols(), nrows()}; }
		
		Size size() const { return {width(), height()}; }
		
		coord_t ncols() const { return m_lr.x() - m_origin.x() + 1; }
		
		coord_t nrows() const { return m_lr.y() - m_origin.y() + 1; }
		
		coord_t width() const { return m_lr.x() - m_origin.x(); }
		
		coord_t height() const { return m_lr.y() - m_origin.y(); }
		
		coord_t offset_x() const { return m_origin.x(); }
		
		coord_t offset_y() const { return m_origin.y(); }
		
		Point center() const { return {center_x(), center_y()}; }
		
		coord_t center_x() const { return m_origin.x() + width() / 2; }
		
		coord_t center_y() const { return m_origin.y() + height() / 2; }
		
		// Set
		void ul(const Point &ul) {
			m_origin = ul;
			dimensions_change();
		}
		
		void ul_x(coord_t v) {
			m_origin.x(v);
			dimensions_change();
		}
		
		void ul_y(coord_t v) {
			m_origin.y(v);
			dimensions_change();
		}
		
		void ur(const Point &ur) {
			m_lr.x(ur.x());
			m_origin.y(ur.y());
			dimensions_change();
		}
		
		void ur_x(coord_t v) {
			m_lr.x(v);
			dimensions_change();
		}
		
		void ur_y(coord_t v) {
			m_origin.y(v);
			dimensions_change();
		}
		
		void lr(const Point &lr) {
			m_lr = lr;
			dimensions_change();
		}
		
		void lr_x(coord_t v) {
			m_lr.x(v);
			dimensions_change();
		}
		
		void lr_y(coord_t v) {
			m_lr.y(v);
			dimensions_change();
		}
		
		void ll(const Point &ll) {
			m_origin.x(ll.x());
			m_lr.y(ll.y());
			dimensions_change();
		}
		
		void ll_x(coord_t v) {
			m_origin.x(v);
			dimensions_change();
		}
		
		void ll_y(coord_t v) {
			m_lr.y(v);
			dimensions_change();
		}
		
		void dim(const Dim &dim) {
			nrows(dim.nrows());
			ncols(dim.ncols());
			dimensions_change();
		}
		
		void ncols(coord_t v) {
			m_lr.x(m_origin.x() + v - 1);
			dimensions_change();
		}
		
		void nrows(coord_t v) {
			m_lr.y(m_origin.y() + v - 1);
			dimensions_change();
		}
		
		void size(const Size &size) {
			width(size.width());
			height(size.height());
			dimensions_change();
		}
		
		void size(coord_t width, coord_t height) {
			this->width(width);
			this->height(height);
			dimensions_change();
		}
		
		void width(coord_t width) {
			m_lr.x(m_origin.x() + width);
			dimensions_change();
		}
		
		void height(coord_t height) {
			m_lr.y(m_origin.y() + height);
			dimensions_change();
		}
		
		void rect_set(const Point &upper_left, const Point &lower_right) {
			m_origin = upper_left;
			m_lr = lower_right;
			dimensions_change();
		}
		
		void rect_set(const Point &upper_left, const Size &size) {
			m_origin = upper_left;
			this->size(size);
			dimensions_change();
		}
		
		void rect_set(const Point &upper_left, const Dim &dim_) {
			m_origin = upper_left;
			dim(dim_);
			dimensions_change();
		}
		
		void offset_x(coord_t v) {
			m_origin.x(v);
			dimensions_change();
		}
		
		void offset_y(coord_t v) {
			m_origin.y(v);
			dimensions_change();
		}
		
		void move(int x, int y) {
			m_origin.move(x, y);
			m_lr.move(x, y);
		}
		
		// containment
		bool contains_x(coord_t v) const {
			if (v >= ul_x() && v <= lr_x())
				return true;
			else
				return false;
		}
		
		bool contains_y(coord_t v) const {
			if (v >= ul_y() && v <= lr_y())
				return true;
			else
				return false;
		}
		
		bool contains_point(const Point &v) const {
			if (contains_x(v.x()) && contains_y(v.y()))
				return true;
			else
				return false;
		}
		
		bool contains_rect(const Rect &v) const {
			if (contains_point(v.ul()) && contains_point(v.lr()))
				return true;
			else
				return false;
		}
		
		Rect expand(size_t expansion) const {
			return Rect(Point(size_t(std::max((long) ul_x() - (long) expansion, 0l)),
			                  size_t(std::max((long) ul_y() - (long) expansion, 0l))),
			            Point(size_t((long) lr_x() + expansion + 1),
			                  size_t((long) lr_y() + expansion + 1)));
		}
		
		// intersection
		bool intersects_x(const Rect &v) const {
			coord_t sul = ul_x();
			coord_t slr = lr_x();
			coord_t vul = v.ul_x();
			coord_t vlr = v.lr_x();
			return (((vul >= sul) && (vul <= slr)) ||
			        ((vlr >= sul) && (vlr <= slr)) ||
			        ((sul >= vul) && (sul <= vlr)) ||
			        ((slr >= vul) && (slr <= vlr)));
		}
		
		bool intersects_y(const Rect &v) const {
			coord_t sul = ul_y();
			coord_t slr = lr_y();
			coord_t vul = v.ul_y();
			coord_t vlr = v.lr_y();
			return (((vul >= sul) && (vul <= slr)) ||
			        ((vlr >= sul) && (vlr <= slr)) ||
			        ((sul >= vul) && (sul <= vlr)) ||
			        ((slr >= vul) && (slr <= vlr)));
		}
		
		bool intersects(const Rect &v) const {
			return (intersects_x(v) && intersects_y(v));
		}
		
		Rect intersection(const Rect &other) const {
			size_t ulx = std::max(ul_x(), other.ul_x());
			size_t uly = std::max(ul_y(), other.ul_y());
			size_t lrx = std::min(lr_x(), other.lr_x());
			size_t lry = std::min(lr_y(), other.lr_y());
			return Rect(Point(ulx, uly), Point(lrx, lry));
		}
		
		// Equality
		bool operator==(const Rect &other) const {
			if (m_origin == other.m_origin && m_lr == other.m_lr)
				return true;
			else
				return false;
		}
		
		bool operator>(const Rect &other) const {
			if (m_origin > other.m_origin && m_lr > other.m_lr)
				return true;
			else
				return (m_origin == other.m_origin && m_lr > other.m_lr);
		}
		
		bool operator!=(const Rect &other) const {
			if (m_origin != other.m_origin || m_lr != other.m_lr)
				return true;
			else
				return false;
		}
		
		// union
		static Rect *union_rects(std::vector<Rect *> &rects) {
			size_t min_x, min_y, max_x, max_y;
			min_x = min_y = std::numeric_limits<size_t>::max();
			max_x = max_y = 0;
			
			for (Rect * rect : rects) {
				min_x = std::min(min_x, rect->ul_x());
				min_y = std::min(min_y, rect->ul_y());
				max_x = std::max(max_x, rect->lr_x());
				max_y = std::max(max_y, rect->lr_y());
			}
			return new Rect(Point(min_x, min_y), Point(max_x, max_y));
		}
		
		void union_rect(const Rect &other) {
			ul_y(std::min(ul_y(), other.ul_y()));
			lr_y(std::max(lr_y(), other.lr_y()));
			ul_x(std::min(ul_x(), other.ul_x()));
			lr_x(std::max(lr_x(), other.lr_x()));
		}
		
		// distance
		double distance_euclid(const Rect &other) {
			return euclid(center_x(), center_y(), other.center_x(), other.center_y());
		}
		
		coord_t distance_cx(const Rect &other) {
			coord_t cx = center_x();
			coord_t other_cx = other.center_x();
			if (cx > other_cx)
				return cx - other_cx;
			else
				return other_cx - cx;
		}
		
		coord_t distance_cy(const Rect &other) {
			coord_t cy = center_y();
			coord_t other_cy = other.center_y();
			if (cy > other_cy)
				return cy - other_cy;
			else
				return other_cy - cy;
		}
		
		double distance_bb(const Rect &other) {
			double min_y = (double) std::min
					(std::min(abs((long) ul_y() - (long) other.ul_y()),
					          abs((long) ul_y() - (long) other.lr_y())),
					 std::min(abs((long) lr_y() - (long) other.ul_y()),
					          abs((long) lr_y() - (long) other.lr_y())));
			double min_x = (double) std::min
					(std::min(abs((long) ul_x() - (long) other.ul_x()),
					          abs((long) ul_x() - (long) other.lr_x())),
					 std::min(abs((long) lr_x() - (long) other.ul_x()),
					          abs((long) lr_x() - (long) other.lr_x())));
			
			return std::sqrt(min_y * min_y + min_x * min_x);
		}
	
	private:
		double euclid(coord_t x1, coord_t y1, coord_t x2, coord_t y2) {
			double dx1 = (double) x1;
			double dy1 = (double) y1;
			double dx2 = (double) x2;
			double dy2 = (double) y2;
			double a = std::pow(std::abs(dx1 - dx2), 2);
			double b = std::pow(std::abs(dy1 - dy2), 2);
			return std::sqrt(a + b);
		}
	
	protected:
		virtual void dimensions_change() {}
	
	private:
		Point m_origin, m_lr;
	};
	
}

#endif
