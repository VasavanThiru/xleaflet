/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_CIRCLE_HPP
#define XLEAFLET_CIRCLE_HPP

#include <array>
#include <string>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xpath.hpp"

namespace xlf
{
    /**********************
     * circle declaration *
     **********************/

    template <class D>
    class xcircle : public xpath<D>
    {
    public:

        using point_type = std::array<double, 2>;

        using base_type = xpath<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        XPROPERTY(point_type, derived_type, location);
        XPROPERTY(int, derived_type, radius, 1000);

    protected:

        xcircle();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using circle = xw::xmaterialize<xcircle>;

    using circle_generator = xw::xgenerator<xcircle>;

    /**************************
     * xcircle implementation *
     **************************/

    template <class D>
    inline xeus::xjson xcircle<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(location, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(radius, state);

        return state;
    }

    template <class D>
    inline void xcircle<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(location, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(radius, patch);
    }

    template <class D>
    inline xcircle<D>::xcircle()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xcircle<D>::set_defaults()
    {
        this->_model_name() = "LeafletCircleModel";
        this->_view_name() = "LeafletCircleView";

        this->options().insert(
            this->options().end(),
            {
                "radius"
            }
        );
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xcircle>;
    extern template xw::xmaterialize<xlf::xcircle>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xcircle>>;
    extern template class xw::xgenerator<xlf::xcircle>;
    extern template xw::xgenerator<xlf::xcircle>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xcircle>>;
#endif

#endif
