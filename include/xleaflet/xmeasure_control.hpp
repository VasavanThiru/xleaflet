/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_MEASURE_CONTROL_HPP
#define XLEAFLET_MEASURE_CONTROL_HPP

#include <string>
#include <vector>

#include "xwidgets/xcolor.hpp"
#include "xwidgets/xholder.hpp"
#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xcontrol.hpp"
#include "xfeature_group.hpp"
#include "xleaflet_config.hpp"

namespace xlf
{
    /*******************************
     * measure_control declaration *
     *******************************/

    // TODO: Add support for custom units like in ipyleaflet

    template <class D>
    class xmeasure_control : public xcontrol<D>
    {
    public:

        using base_type = xcontrol<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, position, "topright", XEITHER("topright", "topleft", "bottomright", "bottomleft"));
        XPROPERTY(std::string, derived_type, primary_length_unit, "feet", XEITHER("feet", "meters", "miles", "kilometers"));
        XPROPERTY(xtl::xoptional<std::string>, derived_type, secondary_length_unit, {}, XEITHER_OPTIONAL("feet", "meters", "miles", "kilometers"));
        XPROPERTY(std::string, derived_type, primary_area_unit, "acres", XEITHER("acres", "hectares", "sqfeet", "sqmeters", "sqmiles"));
        XPROPERTY(xtl::xoptional<std::string>, derived_type, secondary_area_unit, {}, XEITHER_OPTIONAL("acres", "hectares", "sqfeet", "sqmeters", "sqmiles"));
        XPROPERTY(xw::html_color, derived_type, active_color, "#ABE67E");
        XPROPERTY(xw::html_color, derived_type, completed_color, "#C8F2BE");
        XPROPERTY(xeus::xjson, derived_type, popup_options, R"({
            "className": "leaflet-measure-resultpopup",
            "autoPanPadding": [10, 10]
        })"_json);
        XPROPERTY(int, derived_type, capture_z_index, 10000);

    protected:

        xmeasure_control();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using measure_control = xw::xmaterialize<xmeasure_control>;

    using measure_control_generator = xw::xgenerator<xmeasure_control>;

    /********************************
     * xmeasure_control implementation *
     ********************************/

    template <class D>
    inline void xmeasure_control<D>::serialize_state(xeus::xjson& state,
                                                     xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::set_patch_from_property;

        set_patch_from_property(primary_length_unit, state, buffers);
        set_patch_from_property(secondary_length_unit, state, buffers);
        set_patch_from_property(primary_area_unit, state, buffers);
        set_patch_from_property(secondary_area_unit, state, buffers);
        set_patch_from_property(active_color, state, buffers);
        set_patch_from_property(completed_color, state, buffers);
        set_patch_from_property(popup_options, state, buffers);
        set_patch_from_property(capture_z_index, state, buffers);
    }

    template <class D>
    inline void xmeasure_control<D>::apply_patch(const xeus::xjson& patch,
                                                 const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(primary_length_unit, patch, buffers);
        set_property_from_patch(secondary_length_unit, patch, buffers);
        set_property_from_patch(primary_area_unit, patch, buffers);
        set_property_from_patch(secondary_area_unit, patch, buffers);
        set_property_from_patch(active_color, patch, buffers);
        set_property_from_patch(completed_color, patch, buffers);
        set_property_from_patch(popup_options, patch, buffers);
        set_property_from_patch(capture_z_index, patch, buffers);
    }

    template <class D>
    inline xmeasure_control<D>::xmeasure_control()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xmeasure_control<D>::set_defaults()
    {
        this->_model_name() = "LeafletMeasureControlModel";
        this->_view_name() = "LeafletMeasureControlView";
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xmeasure_control>;
    extern template xw::xmaterialize<xlf::xmeasure_control>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xmeasure_control>>;
    extern template class xw::xgenerator<xlf::xmeasure_control>;
    extern template xw::xgenerator<xlf::xmeasure_control>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xmeasure_control>>;
#endif

#endif
