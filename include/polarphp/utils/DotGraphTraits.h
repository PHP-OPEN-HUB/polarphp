//===-- llvm/Support/DOTGraphTraits.h - Customize .dot output ---*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// This source file is part of the polarphp.org open source project
//
// Copyright (c) 2017 - 2019 polarphp software foundation
// Copyright (c) 2017 - 2019 zzu_softboy <zzu_softboy@163.com>
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://polarphp.org/LICENSE.txt for license information
// See https://polarphp.org/CONTRIBUTORS.txt for the list of polarphp project authors
//
// Created by polarboy on 2018/07/01.

#ifndef POLARPHP_UTILS_DOT_GRAPH_TRAITS_H
#define POLARPHP_UTILS_DOT_GRAPH_TRAITS_H

#include <string>

namespace polar::utils {

/// DefaultDotGraphTraits - This class provides the default implementations of
/// all of the DOTGraphTraits methods.  If a specialization does not need to
/// override all methods here it should inherit so that it can get the default
/// implementations.
///
struct DefaultDotGraphTraits
{
private:
   bool m_isSimple;

protected:
   bool isSimple()
   {
      return m_isSimple;
   }

public:
   explicit DefaultDotGraphTraits(bool simple = false)
      : m_isSimple (simple)
   {}

   /// getGraphName - Return the label for the graph as a whole.  Printed at the
   /// top of the graph.
   ///
   template<typename GraphType>
   static std::string getGraphName(const GraphType &)
   {
      return "";
   }

   /// getGraphProperties - Return any custom properties that should be included
   /// in the top level graph structure for dot.
   ///
   template<typename GraphType>
   static std::string getGraphProperties(const GraphType &)
   {
      return "";
   }

   /// renderGraphFromBottomUp - If this function returns true, the graph is
   /// emitted bottom-up instead of top-down.  This requires graphviz 2.0 to work
   /// though.
   static bool renderGraphFromBottomUp()
   {
      return false;
   }

   /// isNodeHidden - If the function returns true, the given node is not
   /// displayed in the graph.
   static bool isNodeHidden(const void *)
   {
      return false;
   }

   /// getNodeLabel - Given a node and a pointer to the top level graph, return
   /// the label to print in the node.
   template<typename GraphType>
   std::string getNodeLabel(const void *, const GraphType &)
   {
      return "";
   }

   // getNodeIdentifierLabel - Returns a string representing the
   // address or other unique identifier of the node. (Only used if
   // non-empty.)
   template <typename GraphType>
   static std::string getNodeIdentifierLabel(const void *, const GraphType &)
   {
      return "";
   }

   template<typename GraphType>
   static std::string getNodeDescription(const void *, const GraphType &)
   {
      return "";
   }

   /// If you want to specify custom node attributes, this is the place to do so
   ///
   template<typename GraphType>
   static std::string getNodeAttributes(const void *,
                                        const GraphType &)
   {
      return "";
   }

   /// If you want to override the dot attributes printed for a particular edge,
   /// override this method.
   template<typename EdgeIter, typename GraphType>
   static std::string getEdgeAttributes(const void *, EdgeIter,
                                        const GraphType &)
   {
      return "";
   }

   /// getEdgeSourceLabel - If you want to label the edge source itself,
   /// implement this method.
   template<typename EdgeIter>
   static std::string getEdgeSourceLabel(const void *, EdgeIter)
   {
      return "";
   }

   /// edgeTargetsEdgeSource - This method returns true if this outgoing edge
   /// should actually target another edge source, not a node.  If this method is
   /// implemented, getEdgeTarget should be implemented.
   template<typename EdgeIter>
   static bool edgeTargetsEdgeSource(const void *, EdgeIter)
   {
      return false;
   }

   /// getEdgeTarget - If edgeTargetsEdgeSource returns true, this method is
   /// called to determine which outgoing edge of Node is the target of this
   /// edge.
   template<typename EdgeIter>
   static EdgeIter getEdgeTarget(const void *, EdgeIter iter)
   {
      return iter;
   }

   /// hasEdgeDestLabels - If this function returns true, the graph is able
   /// to provide labels for edge destinations.
   static bool hasEdgeDestLabels()
   {
      return false;
   }

   /// numEdgeDestLabels - If hasEdgeDestLabels, this function returns the
   /// number of incoming edge labels the given node has.
   static unsigned numEdgeDestLabels(const void *)
   {
      return 0;
   }

   /// getEdgeDestLabel - If hasEdgeDestLabels, this function returns the
   /// incoming edge label with the given index in the given node.
   static std::string getEdgeDestLabel(const void *, unsigned)
   {
      return "";
   }

   /// addCustomGraphFeatures - If a graph is made up of more than just
   /// straight-forward nodes and edges, this is the place to put all of the
   /// custom stuff necessary.  The GraphWriter object, instantiated with your
   /// GraphType is passed in as an argument.  You may call arbitrary methods on
   /// it to add things to the output graph.
   ///
   template<typename GraphType, typename GraphWriter>
   static void addCustomGraphFeatures(const GraphType &, GraphWriter &)
   {}
};


/// DOTGraphTraits - Template class that can be specialized to customize how
/// graphs are converted to 'dot' graphs.  When specializing, you may inherit
/// from DefaultDotGraphTraits if you don't need to override everything.
///
template <typename Ty>
struct DOTGraphTraits : public DefaultDotGraphTraits
{
   DOTGraphTraits (bool simple = false)
      : DefaultDotGraphTraits (simple)
   {}
};

} // polar::utils

#endif // POLARPHP_UTILS_DOT_GRAPH_TRAITS_H
