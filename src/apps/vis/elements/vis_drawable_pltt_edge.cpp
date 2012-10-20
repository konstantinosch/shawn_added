#include "../buildfiles/_apps_enable_cmake.h"
#ifdef ENABLE_VIS
#include "apps/vis/elements/vis_drawable_pltt_edge.h"
namespace vis
{
	const std::string DrawablePLTTEdge::PREFIX("pltt.");
	// ----------------------------------------------------------------------
	DrawablePLTTEdge::DrawablePLTTEdge( const shawn::Node& v1, const shawn::Node& v2, const DrawableNode& dv1, const DrawableNode& dv2, const std::string& p ) :
		DrawableEdge( std::string("edge.") + p, v1, v2 ),
		props_ ( NULL ),
		src_drawable_ ( &dv1 ),
		tgt_drawable_ ( &dv2 )
		{}
	// ----------------------------------------------------------------------
	DrawablePLTTEdge::~DrawablePLTTEdge()
	{}
	// ----------------------------------------------------------------------
	void DrawablePLTTEdge::init( void ) throw()
	{
		props_ = new EdgePropertySet;
		props_->init(*this);
		DrawableEdge::init();
	}
	// ----------------------------------------------------------------------
	void DrawablePLTTEdge::draw( cairo_t* cr, double t, const Context& C ) const throw(std::runtime_error)
	{
		Drawable::draw(cr,t,C);
		shawn::Vec pos1 = src_drawable_->position(t);
		shawn::Vec pos2 = tgt_drawable_->position(t);
		double lw       = edge_properties().line_width(t);
		shawn::Vec col  = edge_properties().color(t);
		double blend   = edge_properties().blend(t);
		cairo_save(cr);
		cairo_set_line_width( cr, this->Width );
		cairo_set_source_rgba(cr,R,G,B,1.0-blend);
		cairo_move_to(cr,pos1.x(),pos1.y());
		cairo_line_to(cr,pos2.x(),pos2.y());
		cairo_stroke(cr);
		cairo_restore(cr);
	}
	// ----------------------------------------------------------------------
	const PropertySet& DrawablePLTTEdge::properties( void ) const throw()
	{
		assert( props_.is_not_null() );
		return *props_;
	}
	// ----------------------------------------------------------------------
	PropertySet& DrawablePLTTEdge::properties_w( void ) throw()
	{
		assert( props_.is_not_null() );
		return *props_;
	}
}
#endif
