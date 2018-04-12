/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, and Wolf Vollprecht   *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_TILE_LAYER_HPP
#define XLEAFLET_TILE_LAYER_HPP

#include <string>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xleaflet_config.hpp"
#include "xraster_layer.hpp"

namespace xleaflet
{
    /**************************
     * tile_layer declaration *
     **************************/

    template <class D>
    class xtile_layer : public xraster_layer<D>
    {
    public:

        using load_callback_type = std::function<void(const xeus::xjson&)>;

        using base_type = xraster_layer<D>;
        using derived_type = D;

        xeus::xjson get_state() const;
        void apply_patch(const xeus::xjson&);

        void on_load(load_callback_type);

        void handle_custom_message(const xeus::xjson&);

        XPROPERTY(
            std::string, derived_type, url,
            "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png");
        XPROPERTY(int, derived_type, min_zoom, 0);
        XPROPERTY(int, derived_type, max_zoom, 18);
        XPROPERTY(int, derived_type, tile_size, 256);
        XPROPERTY(
            std::string, derived_type, attribution,
            "Map data (c) <a href=\"https://openstreetmap.org\">OpenStreetMap</a> contributors");
        XPROPERTY(bool, derived_type, detect_retina, false);

    protected:

        xtile_layer();
        using base_type::base_type;

    private:

        void set_defaults();

        std::list<load_callback_type> m_load_callbacks;
    };

    using tile_layer = xw::xmaterialize<xtile_layer>;

    using tile_layer_generator = xw::xgenerator<xtile_layer>;

    /******************************
     * xtile_layer implementation *
     ******************************/

    template <class D>
    inline xeus::xjson xtile_layer<D>::get_state() const
    {
        xeus::xjson state = base_type::get_state();

        XOBJECT_SET_PATCH_FROM_PROPERTY(url, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(min_zoom, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(max_zoom, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(tile_size, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(attribution, state);
        XOBJECT_SET_PATCH_FROM_PROPERTY(detect_retina, state);

        return state;
    }

    template <class D>
    inline void xtile_layer<D>::apply_patch(const xeus::xjson& patch)
    {
        base_type::apply_patch(patch);

        XOBJECT_SET_PROPERTY_FROM_PATCH(url, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(min_zoom, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(max_zoom, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(tile_size, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(attribution, patch);
        XOBJECT_SET_PROPERTY_FROM_PATCH(detect_retina, patch);
    }

    template <class D>
    inline void xtile_layer<D>::on_load(load_callback_type callback)
    {
        m_load_callbacks.emplace_back(std::move(callback));
    }

    template <class D>
    inline xtile_layer<D>::xtile_layer()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xtile_layer<D>::set_defaults()
    {
        this->_model_name() = "LeafletTileLayerModel";
        this->_view_name() = "LeafletTileLayerView";

        this->bottom() = true;

        this->options().insert(
            this->options().end(),
            {
                "min_zoom",
                "max_zoom",
                "tile_size",
                "attribution",
                "detect_retina"
            }
        );
    }

    template <class D>
    inline void xtile_layer<D>::handle_custom_message(const xeus::xjson& content)
    {
        auto it = content.find("event");
        if (it != content.end() && it.value() == "load")
        {
            for (auto it = m_load_callbacks.begin(); it != m_load_callbacks.end(); ++it)
            {
                it->operator()(content);
            }
        }
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xleaflet::xtile_layer>;
    extern template xw::xmaterialize<xleaflet::xtile_layer>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xleaflet::xtile_layer>>;
    extern template class xw::xgenerator<xleaflet::xtile_layer>;
    extern template xw::xgenerator<xleaflet::xtile_layer>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xleaflet::xtile_layer>>;
#endif

#endif
