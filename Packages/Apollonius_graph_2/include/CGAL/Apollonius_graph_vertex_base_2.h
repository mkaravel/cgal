// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       : 
// release_date  : 
//
// file          : include/CGAL/Apollonius_graph_vertex_base_2.h
// package       : Apollonius_graph_2
// source        : $RCSfile$
// revision      : $Revision$
// revision_date : $Date$
// author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>
//
// coordinator   : Mariette Yvinec  <Mariette Yvinec@sophia.inria.fr>
//
// ======================================================================



#ifndef CGAL_APOLLONIUS_GRAPH_VERTEX_BASE_2_H
#define CGAL_APOLLONIUS_GRAPH_VERTEX_BASE_2_H

#include <list>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/triangulation_assertions.h>

CGAL_BEGIN_NAMESPACE


template <class Gt,
	  bool StoreHidden = true,
	  class Vb = Triangulation_ds_vertex_base_2<> >
class Apollonius_graph_vertex_base_2
  : private Triangulation_vertex_base_2<Gt,Vb>
{
private:
  typedef typename Vb::Triangulation_data_structure   AGDS;
public:
  // TYPES
  //------
  typedef Gt                             Geom_traits;
  typedef typename Gt::Weighted_point_2  Weighted_point_2;
  typedef AGDS	                         Apollonius_graph_data_structure;
  typedef typename AGDS::Face_handle     Face_handle;
  typedef typename AGDS::Vertex_handle   Vertex_handle;

  template < typename AGDS2 >
  struct Rebind_TDS {
    typedef typename Vb::template Rebind_TDS<AGDS2>::Other      Vb2;
    typedef Apollonius_graph_vertex_base_2<Gt,StoreHidden,Vb2>  Other;
  };


private:
  // local types
  typedef std::list<Weighted_point_2>         Container;
  typedef Triangulation_vertex_base_2<Gt,Vb>  Vbase;
public:
  // TYPES (continued)
  //------------------
  typedef Container                        Hidden_weighted_point_container;
  typedef typename Container::iterator     Hidden_weighted_point_iterator;

public:
  // CREATION
  //---------
  Apollonius_graph_vertex_base_2() : Vbase() {}

  Apollonius_graph_vertex_base_2(const Weighted_point_2& p, void* f = NULL) 
    : Vbase(p, f) {}

  ~Apollonius_graph_vertex_base_2()
  {
    clear_hidden_weighted_point_container();
  }


  // ACCESS METHODS
  //---------------
  inline Weighted_point_2 point() const { return Vbase::point(); }

  inline Face_handle face() const { return Vbase::face(); }

  inline unsigned int number_of_hidden_weighted_points() const {
    return weighted_point_list.size();
  }

  inline
  Hidden_weighted_point_iterator hidden_weighted_points_begin() { 
    return weighted_point_list.begin();
  }

  inline
  Hidden_weighted_point_iterator hidden_weighted_points_end() {
    return weighted_point_list.end();
  }

public:
  // SETTING AND UNSETTING
  //----------------------
  inline void set_point(const Weighted_point_2& p) {
    Vbase::set_point(p);
  }

  inline void set_face(Face_handle f) { Vbase::set_face(f); }

  inline
  void add_hidden_weighted_point(const Weighted_point_2& p)
  {
    if ( StoreHidden ) {
      weighted_point_list.push_back(p);
    }
  }

  inline
  void clear_hidden_weighted_point_container()
  {
    weighted_point_list.clear();
  }

public:
  // VALIDITY CHECK
  inline bool is_valid(bool verbose, int level) const {
    return Vbase::is_valid(verbose, level);
  }

private:
  // class variables
  Container weighted_point_list;
};

CGAL_END_NAMESPACE 

#endif // CGAL_APOLLONIUS_GRAPH_VERTEX_BASE_2_H
