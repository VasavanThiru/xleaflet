/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_VIDEO_OVERLAY_HPP
#define XLEAFLET_VIDEO_OVERLAY_HPP

#include <array>
#include <string>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xleaflet_config.hpp"
#include "xraster_layer.hpp"

namespace xlf
{
    /*****************************
     * video_overlay declaration *
     *****************************/

    template <class D>
    class xvideo_overlay : public xraster_layer<D>
    {
    public:

        using point_type = std::array<double, 2>;
        using bounds_type = std::array<point_type, 2>;

        using base_type = xraster_layer<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, url, "");
        XPROPERTY(bounds_type, derived_type, bounds);
        XPROPERTY(std::string, derived_type, attribution, "");

    protected:

        xvideo_overlay();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using video_overlay = xw::xmaterialize<xvideo_overlay>;

    using video_overlay_generator = xw::xgenerator<xvideo_overlay>;

    /********************************
     * video_overlay implementation *
     ********************************/

    template <class D>
    inline void xvideo_overlay<D>::serialize_state(xeus::xjson& state,
                                                   xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        using xw::set_patch_from_property;

        set_patch_from_property(url, state, buffers);
        set_patch_from_property(bounds, state, buffers);
        set_patch_from_property(attribution, state, buffers);
    }

    template <class D>
    inline void xvideo_overlay<D>::apply_patch(const xeus::xjson& patch,
                                               const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        using xw::set_property_from_patch;

        set_property_from_patch(url, patch, buffers);
        set_property_from_patch(bounds, patch, buffers);
        set_property_from_patch(attribution, patch, buffers);
    }

    template <class D>
    inline xvideo_overlay<D>::xvideo_overlay()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xvideo_overlay<D>::set_defaults()
    {
        this->_model_name() = "LeafletVideoOverlayModel";
        this->_view_name() = "LeafletVideoOverlayView";

        this->bounds() = {{{0, 0}, {0, 0}}};

        this->options().insert(
            this->options().end(),
            {
                "attribution"
            }
        );
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xvideo_overlay>;
    extern template xw::xmaterialize<xlf::xvideo_overlay>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xvideo_overlay>>;
    extern template class xw::xgenerator<xlf::xvideo_overlay>;
    extern template xw::xgenerator<xlf::xvideo_overlay>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xvideo_overlay>>;
#endif

#endif
