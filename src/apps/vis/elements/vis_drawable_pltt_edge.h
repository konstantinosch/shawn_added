#ifndef __SHAWN_VIS_DRAWABLE_PLTT_EDGE_H
#define __SHAWN_VIS_DRAWABLE_PLTT_EDGE_H
#include "../buildfiles/_apps_enable_cmake.h"
#ifdef ENABLE_VIS
#include "apps/vis/elements/vis_drawable_edge.h"
#include "apps/vis/elements/vis_drawable_node.h"
#include "apps/vis/elements/vis_drawable_node.h"
#include "apps/vis/properties/vis_edge_property_set.h"
#include "apps/vis/base/vis_needs_cairo.h"
namespace vis
{
	class DrawablePLTTEdge : public DrawableEdge
	{
		public:
			DrawablePLTTEdge( const shawn::Node&, const shawn::Node&, const DrawableNode&, const DrawableNode&, const std::string& p = PREFIX);
			virtual ~DrawablePLTTEdge();
			virtual void init( void ) throw();
			virtual void draw( cairo_t*, double, const Context& ) const throw(std::runtime_error);
			virtual const PropertySet& properties( void ) const throw();
			virtual PropertySet& properties_w( void ) throw();
			inline EdgePropertySet& edge_properties_w( void ) throw()
			{ assert( props_.is_not_null() ); return *props_; }
			inline const EdgePropertySet& edge_properties( void ) const throw()
			{ assert( props_.is_not_null() ); return *props_; }
			static const std::string PREFIX;
			double R;
			double G;
			double B;
			double Width;
		private:
			shawn::RefcntPointer<EdgePropertySet> props_;
			const DrawableNode* src_drawable_;
			const DrawableNode* tgt_drawable_;
	};
}
#endif
#endif
