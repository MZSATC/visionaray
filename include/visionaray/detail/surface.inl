// This file is distributed under the MIT license.
// See the LICENSE file for details.

#pragma once

#ifndef VSNRAY_SURFACE_INL
#define VSNRAY_SURFACE_INL 1

#include <iterator>
#include <stdexcept>

#include "../generic_material.h"
#include "../generic_primitive.h"
#include "../get_color.h"
#include "../get_normal.h"
#include "../get_tex_coord.h"
#include "../tags.h"

namespace visionaray
{
namespace detail
{

//-------------------------------------------------------------------------------------------------
// Helper functions
//

template <typename N, typename M>
VSNRAY_FUNC
surface<N, M> make_surface(N const& n, M const& m)
{
    return surface<N, M>(n, m);
}

template <typename N, typename M, typename C>
VSNRAY_FUNC
surface<N, M, C> make_surface(N const& n, M const m, C const& tex_color)
{
    return surface<N, M, C>(n, m, tex_color);
}


// deduce surface type from params ------------------------

template <typename ...Args>
struct decl_surface;

template <
    typename Normals,
    typename Materials
    >
struct decl_surface<Normals, Materials>
{
    using type = surface<
        typename std::iterator_traits<Normals>::value_type,
        typename std::iterator_traits<Materials>::value_type
        >;
};

template <
    typename Normals,
    typename Materials,
    typename DiffuseColor
    >
struct decl_surface<Normals, Materials, DiffuseColor>
{
    using type = surface<
        typename std::iterator_traits<Normals>::value_type,
        typename std::iterator_traits<Materials>::value_type,
        DiffuseColor
        >;
};


// identify accelerators ----------------------------------

template <typename T>
struct primitive_traits
{
    using type = T;
};

template <template <typename> class Accelerator, typename T>
struct primitive_traits<Accelerator<T>>
{
    using type = T;
};


} // detail


namespace simd
{

//-------------------------------------------------------------------------------------------------
// Functions to pack and unpack SIMD surfaces
//

template <typename N, typename M, typename ...Args>
inline auto pack(
        surface<N, M, Args...> const& s1,
        surface<N, M, Args...> const& s2,
        surface<N, M, Args...> const& s3,
        surface<N, M, Args...> const& s4
        ) -> decltype( visionaray::detail::make_surface(
            pack(
                s1.normal,
                s2.normal,
                s3.normal,
                s4.normal
                ),
            pack(
                s1.material,
                s2.material,
                s3.material,
                s4.material
                )
            ) )

{
    return visionaray::detail::make_surface(
            pack(
                s1.normal,
                s2.normal,
                s3.normal,
                s4.normal
                ),
            pack(
                s1.material,
                s2.material,
                s3.material,
                s4.material
                )
            );
}

template <typename N, typename M, typename C, typename ...Args>
inline auto pack(
        surface<N, M, C, Args...> const& s1,
        surface<N, M, C, Args...> const& s2,
        surface<N, M, C, Args...> const& s3,
        surface<N, M, C, Args...> const& s4
        ) -> decltype( visionaray::detail::make_surface(
            pack(
                s1.normal,
                s2.normal,
                s3.normal,
                s4.normal
                ),
            pack(
                s1.material,
                s2.material,
                s3.material,
                s4.material
                ),
            pack(
                s1.tex_color_,
                s2.tex_color_,
                s3.tex_color_,
                s4.tex_color_
                )
            ) )
{
    return visionaray::detail::make_surface(
            pack(
                s1.normal,
                s2.normal,
                s3.normal,
                s4.normal
                ),
            pack(
                s1.material,
                s2.material,
                s3.material,
                s4.material
                ),
            pack(
                s1.tex_color_,
                s2.tex_color_,
                s3.tex_color_,
                s4.tex_color_
                )
            );
}

#if VSNRAY_SIMD_ISA >= VSNRAY_SIMD_ISA_AVX

template <typename N, typename M, typename ...Args>
inline auto pack(
        surface<N, M, Args...> const& s1,
        surface<N, M, Args...> const& s2,
        surface<N, M, Args...> const& s3,
        surface<N, M, Args...> const& s4,
        surface<N, M, Args...> const& s5,
        surface<N, M, Args...> const& s6,
        surface<N, M, Args...> const& s7,
        surface<N, M, Args...> const& s8
        ) -> decltype( visionaray::detail::make_surface(
            pack(
                s1.normal,
                s2.normal,
                s3.normal,
                s4.normal,
                s5.normal,
                s6.normal,
                s7.normal,
                s8.normal
                ),
            pack(
                s1.material,
                s2.material,
                s3.material,
                s4.material,
                s5.material,
                s6.material,
                s7.material,
                s8.material
                )
            ) )
{
    return visionaray::detail::make_surface(
            pack(
                s1.normal,
                s2.normal,
                s3.normal,
                s4.normal,
                s5.normal,
                s6.normal,
                s7.normal,
                s8.normal
                ),
            pack(
                s1.material,
                s2.material,
                s3.material,
                s4.material,
                s5.material,
                s6.material,
                s7.material,
                s8.material
                )
            );
}

template <typename N, typename M, typename C, typename ...Args>
inline auto pack(
        surface<N, M, C, Args...> const& s1,
        surface<N, M, C, Args...> const& s2,
        surface<N, M, C, Args...> const& s3,
        surface<N, M, C, Args...> const& s4,
        surface<N, M, C, Args...> const& s5,
        surface<N, M, C, Args...> const& s6,
        surface<N, M, C, Args...> const& s7,
        surface<N, M, C, Args...> const& s8
        ) -> decltype( visionaray::detail::make_surface(
            pack(
                s1.normal,
                s2.normal,
                s3.normal,
                s4.normal,
                s5.normal,
                s6.normal,
                s7.normal,
                s8.normal
                ),
            pack(
                s1.material,
                s2.material,
                s3.material,
                s4.material,
                s5.material,
                s6.material,
                s7.material,
                s8.material
                ),
            pack(
                s1.tex_color_,
                s2.tex_color_,
                s3.tex_color_,
                s4.tex_color_,
                s5.tex_color_,
                s6.tex_color_,
                s7.tex_color_,
                s8.tex_color_
                )
            ) )
{
    return visionaray::detail::make_surface(
            pack(
                s1.normal,
                s2.normal,
                s3.normal,
                s4.normal,
                s5.normal,
                s6.normal,
                s7.normal,
                s8.normal
                ),
            pack(
                s1.material,
                s2.material,
                s3.material,
                s4.material,
                s5.material,
                s6.material,
                s7.material,
                s8.material
                ),
            pack(
                s1.tex_color_,
                s2.tex_color_,
                s3.tex_color_,
                s4.tex_color_,
                s5.tex_color_,
                s6.tex_color_,
                s7.tex_color_,
                s8.tex_color_
                )
            );
}

#endif // VSNRAY_SIMD_ISA >= VSNRAY_SIMD_ISA_AVX

} // simd


//-------------------------------------------------------------------------------------------------
//
//

template <
    typename HR,
    typename Normals,
    typename Materials,
    typename Primitive,
    typename NormalBinding
    >
VSNRAY_FUNC
inline auto get_surface_any_prim_impl(
        HR const&       hr,
        Normals         normals,
        Materials       materials,
        Primitive       /* */,
        NormalBinding   /* */
        )
    -> typename detail::decl_surface<Normals, Materials>::type
{
    return detail::make_surface(
            get_normal(normals, hr, Primitive{}, NormalBinding{}),
            materials[hr.geom_id]
            );
}

template <
    typename HR,
    typename Normals,
    typename TexCoords,
    typename Materials,
    typename Textures,
    typename Primitive,
    typename NormalBinding
    >
VSNRAY_FUNC
inline auto get_surface_any_prim_impl(
        HR const&       hr,
        Normals         normals,
        TexCoords       tex_coords,
        Materials       materials,
        Textures        textures,
        Primitive       /* */,
        NormalBinding   /* */
        )
    -> typename detail::decl_surface<Normals, Materials, vector<3, float>>::type
{
    using P = typename detail::primitive_traits<Primitive>::type;
    using C = vector<3, float>;

    auto tc = get_tex_coord(tex_coords, hr, P{});

    auto const& tex = textures[hr.geom_id];
    auto tex_color = tex.width() > 0 && tex.height() > 0
                   ? C(tex2D(tex, tc))
                   : C(1.0);

    auto normal = get_normal(normals, hr, P{}, NormalBinding{});
    return detail::make_surface( normal, materials[hr.geom_id], tex_color );
}

template <
    typename HR,
    typename Normals,
    typename TexCoords,
    typename Materials,
    typename Colors,
    typename Textures,
    typename Primitive,
    typename NormalBinding,
    typename ColorBinding
    >
VSNRAY_FUNC
inline auto get_surface_any_prim_impl(
        HR const&       hr,
        Normals         normals,
        TexCoords       tex_coords,
        Materials       materials,
        Colors          colors,
        Textures        textures,
        Primitive       /* */,
        NormalBinding   /* */,
        ColorBinding    /* */
        )
    -> typename detail::decl_surface<Normals, Materials, vector<3, float>>::type
{
    using P = typename detail::primitive_traits<Primitive>::type;
    using C = vector<3, float>;

    auto color = get_color(colors, hr, P{}, ColorBinding{});
    auto tc = get_tex_coord(tex_coords, hr, P{});

    auto const& tex = textures[hr.geom_id];
    auto tex_color = tex.width() > 0 && tex.height() > 0
                   ? C(tex2D(tex, tc))
                   : C(1.0);

    auto normal = get_normal(normals, hr, P{}, NormalBinding{});
    return detail::make_surface( normal, materials[hr.geom_id], color * tex_color );
}


//-------------------------------------------------------------------------------------------------
// Generic primitive / float
//

namespace detail
{

template <typename NormalBinding, typename Normals, typename HR>
class get_normal_from_generic_primitive_visitor
{
public:

    using return_type = vector<3, float>;

public:

    VSNRAY_FUNC
    get_normal_from_generic_primitive_visitor(
            Normals     normals,
            HR const&   hr
            )
        : normals_(normals)
        , hr_(hr)
    {
    }

    VSNRAY_FUNC
    return_type operator()(basic_sphere<float> const& sphere) const
    {
        return get_normal(hr_, sphere, NormalBinding{}); // TODO
    }

    template <typename Primitive>
    VSNRAY_FUNC
    return_type operator()(Primitive const& primitive) const
    {
        VSNRAY_UNUSED(primitive);

        return get_normal(normals_, hr_, primitive, NormalBinding{});
    }

private:

    Normals     normals_;
    HR const&   hr_;

};

} // detail

template <
    typename HR,
    typename NormalBinding,
    typename Primitives,
    typename Normals,
    typename Materials,
    typename ...Ts
    >
VSNRAY_FUNC
inline auto get_surface_with_prims_impl(
        HR const&                   hr,
        Primitives                  primitives,
        Normals                     normals,
        Materials                   materials,
        generic_primitive<Ts...>    /* */,
        NormalBinding               /* */
        )
    -> typename detail::decl_surface<Normals, Materials>::type
{
    detail::get_normal_from_generic_primitive_visitor<NormalBinding, Normals, HR> visitor(
            normals,
            hr
            );

    auto n = apply_visitor( visitor, primitives[hr.prim_id] );
    return detail::make_surface( n, materials[hr.geom_id] );
}


//-------------------------------------------------------------------------------------------------
// Primitive with precalculated normals / float4
//

template <
    template <typename, typename> class HR,
    typename HRP,
    typename Normals,
    typename Materials,
    typename Primitive,
    typename NormalBinding
    >
inline auto get_surface_any_prim_impl(
        HR<simd::ray4, HRP> const&  hr,
        Normals                     normals,
        Materials                   materials,
        Primitive                   /* */,
        NormalBinding               /* */
        ) -> decltype( simd::pack(
            typename detail::decl_surface<Normals, Materials>::type{},
            typename detail::decl_surface<Normals, Materials>::type{},
            typename detail::decl_surface<Normals, Materials>::type{},
            typename detail::decl_surface<Normals, Materials>::type{}
            ) )
{
    using N = typename std::iterator_traits<Normals>::value_type;
    using M = typename std::iterator_traits<Materials>::value_type;
    using P = typename detail::primitive_traits<Primitive>::type;

    auto hr4 = unpack(hr);

    return simd::pack(
        detail::make_surface(
            hr4[0].hit ? get_normal(normals, hr4[0], P{}, NormalBinding{}) : N{},
            hr4[0].hit ? materials[hr4[0].geom_id]                         : M{}
            ),
        detail::make_surface(
            hr4[1].hit ? get_normal(normals, hr4[1], P{}, NormalBinding{}) : N{},
            hr4[1].hit ? materials[hr4[1].geom_id]                         : M{}
            ),
        detail::make_surface(
            hr4[2].hit ? get_normal(normals, hr4[2], P{}, NormalBinding{}) : N{},
            hr4[2].hit ? materials[hr4[2].geom_id]                         : M{}
            ),
        detail::make_surface(
            hr4[3].hit ? get_normal(normals, hr4[3], P{}, NormalBinding{}) : N{},
            hr4[3].hit ? materials[hr4[3].geom_id]                         : M{}
            )
        );
}


template <
    template <typename, typename> class HR,
    typename HRP,
    typename Normals,
    typename TexCoords,
    typename Materials,
    typename Textures,
    typename Primitive,
    typename NormalBinding
    >
inline auto get_surface_any_prim_impl(
        HR<simd::ray4, HRP> const&  hr,
        Normals                     normals,
        TexCoords                   tex_coords,
        Materials                   materials,
        Textures                    textures,
        Primitive                   /* */,
        NormalBinding               /* */
        ) -> decltype( simd::pack(
            typename detail::decl_surface<Normals, Materials, vector<3, float>>::type{},
            typename detail::decl_surface<Normals, Materials, vector<3, float>>::type{},
            typename detail::decl_surface<Normals, Materials, vector<3, float>>::type{},
            typename detail::decl_surface<Normals, Materials, vector<3, float>>::type{}
            ) )
{
    using N = typename std::iterator_traits<Normals>::value_type;
    using M = typename std::iterator_traits<Materials>::value_type;
    using P = typename detail::primitive_traits<Primitive>::type;
    using C = vector<3, float>;

    auto hr4 = unpack(hr);

    auto tc4 = get_tex_coord(tex_coords, hr4, typename detail::primitive_traits<Primitive>::type{});

    C tex_color4[4];
    for (unsigned i = 0; i < 4; ++i)
    {
        if (!hr4[i].hit)
        {
            continue;
        }

        auto const& tex = textures[hr4[i].geom_id];
        tex_color4[i] = tex.width() > 0 && tex.height() > 0
                      ? C(tex2D(tex, tc4[i]))
                      : C(1.0);
    }

    return simd::pack(
        detail::make_surface(
            hr4[0].hit ? get_normal(normals, hr4[0], P{}, NormalBinding{}) : N{},
            hr4[0].hit ? materials[hr4[0].geom_id]                         : M{},
            hr4[0].hit ? tex_color4[0]                                     : C(1.0)
            ),
        detail::make_surface(
            hr4[1].hit ? get_normal(normals, hr4[1], P{}, NormalBinding{}) : N{},
            hr4[1].hit ? materials[hr4[1].geom_id]                         : M{},
            hr4[1].hit ? tex_color4[1]                                     : C(1.0)
            ),
        detail::make_surface(
            hr4[2].hit ? get_normal(normals, hr4[2], P{}, NormalBinding{}) : N{},
            hr4[2].hit ? materials[hr4[2].geom_id]                         : M{},
            hr4[2].hit ? tex_color4[2]                                     : C(1.0)
            ),
        detail::make_surface(
            hr4[3].hit ? get_normal(normals, hr4[3], P{}, NormalBinding{}) : N{},
            hr4[3].hit ? materials[hr4[3].geom_id]                         : M{},
            hr4[3].hit ? tex_color4[3]                                     : C(1.0)
            )
        );
}

template <
    template <typename, typename> class HR,
    typename HRP,
    typename Normals,
    typename TexCoords,
    typename Materials,
    typename Colors,
    typename Textures,
    typename Primitive,
    typename NormalBinding,
    typename ColorBinding
    >
inline auto get_surface_any_prim_impl(
        HR<simd::ray4, HRP> const&  hr,
        Normals                     normals,
        TexCoords                   tex_coords,
        Materials                   materials,
        Colors                      colors,
        Textures                    textures,
        Primitive                   /* */,
        NormalBinding               /* */,
        ColorBinding                /* */
        ) -> decltype( simd::pack(
            typename detail::decl_surface<Normals, Materials, vector<3, float>>::type{},
            typename detail::decl_surface<Normals, Materials, vector<3, float>>::type{},
            typename detail::decl_surface<Normals, Materials, vector<3, float>>::type{},
            typename detail::decl_surface<Normals, Materials, vector<3, float>>::type{}
            ) )
{
    using N = typename std::iterator_traits<Normals>::value_type;
    using M = typename std::iterator_traits<Materials>::value_type;
    using P = typename detail::primitive_traits<Primitive>::type;
    using C = vector<3, float>;

    auto hr4 = unpack(hr);

    auto color4 = get_color(colors, hr4, typename detail::primitive_traits<Primitive>::type{}, ColorBinding{});

    auto tc4 = get_tex_coord(tex_coords, hr4, typename detail::primitive_traits<Primitive>::type{});

    C tex_color4[4];
    for (unsigned i = 0; i < 4; ++i)
    {
        if (!hr4[i].hit)
        {
            continue;
        }

        auto const& tex = textures[hr4[i].geom_id];
        tex_color4[i] = tex.width() > 0 && tex.height() > 0
                      ? C(tex2D(tex, tc4[i]))
                      : C(1.0);
    }

    return simd::pack(
        detail::make_surface(
            hr4[0].hit ? get_normal(normals, hr4[0], P{}, NormalBinding{}) : N{},
            hr4[0].hit ? materials[hr4[0].geom_id]                         : M{},
            hr4[0].hit ? color4[0] * tex_color4[0]                         : C(1.0)
            ),
        detail::make_surface(
            hr4[1].hit ? get_normal(normals, hr4[1], P{}, NormalBinding{}) : N{},
            hr4[1].hit ? materials[hr4[1].geom_id]                         : M{},
            hr4[1].hit ? color4[1] * tex_color4[1]                         : C(1.0)
            ),
        detail::make_surface(
            hr4[2].hit ? get_normal(normals, hr4[2], P{}, NormalBinding{}) : N{},
            hr4[2].hit ? materials[hr4[2].geom_id]                         : M{},
            hr4[2].hit ? color4[2] * tex_color4[2]                         : C(1.0)
            ),
        detail::make_surface(
            hr4[3].hit ? get_normal(normals, hr4[3], P{}, NormalBinding{}) : N{},
            hr4[3].hit ? materials[hr4[3].geom_id]                         : M{},
            hr4[3].hit ? color4[3] * tex_color4[3]                         : C(1.0)
            )
        );
}


#if VSNRAY_SIMD_ISA >= VSNRAY_SIMD_ISA_AVX

//-------------------------------------------------------------------------------------------------
// Primitive with precalculated normals / float8
//

template <
    template <typename, typename> class HR,
    typename HRP,
    typename Normals,
    typename Materials,
    typename Primitive,
    typename NormalBinding
    >
inline auto get_surface_any_prim_impl(
        HR<simd::ray8, HRP> const&  hr,
        Normals                     normals,
        Materials                   materials,
        Primitive                   /* */,
        NormalBinding               /* */
        ) -> decltype( simd::pack(
            typename detail::decl_surface<Normals, Materials>::type{},
            typename detail::decl_surface<Normals, Materials>::type{},
            typename detail::decl_surface<Normals, Materials>::type{},
            typename detail::decl_surface<Normals, Materials>::type{},
            typename detail::decl_surface<Normals, Materials>::type{},
            typename detail::decl_surface<Normals, Materials>::type{},
            typename detail::decl_surface<Normals, Materials>::type{},
            typename detail::decl_surface<Normals, Materials>::type{}
            ) )
{
    using N = typename std::iterator_traits<Normals>::value_type;
    using M = typename std::iterator_traits<Materials>::value_type;
    using P = typename detail::primitive_traits<Primitive>::type;

    auto hr8 = unpack(hr);

    return simd::pack(
        detail::make_surface(
            hr8[0].hit ? get_normal(normals, hr8[0], P{}, NormalBinding{}) : N{},
            hr8[0].hit ? materials[hr8[0].geom_id]                         : M{}
            ),
        detail::make_surface(
            hr8[1].hit ? get_normal(normals, hr8[1], P{}, NormalBinding{}) : N{},
            hr8[1].hit ? materials[hr8[1].geom_id]                         : M{}
            ),
        detail::make_surface(
            hr8[2].hit ? get_normal(normals, hr8[2], P{}, NormalBinding{}) : N{},
            hr8[2].hit ? materials[hr8[2].geom_id]                         : M{}
            ),
        detail::make_surface(
            hr8[3].hit ? get_normal(normals, hr8[3], P{}, NormalBinding{}) : N{},
            hr8[3].hit ? materials[hr8[3].geom_id]                         : M{}
            ),
        detail::make_surface(
            hr8[4].hit ? get_normal(normals, hr8[4], P{}, NormalBinding{}) : N{},
            hr8[4].hit ? materials[hr8[4].geom_id]                         : M{}
            ),
        detail::make_surface(
            hr8[5].hit ? get_normal(normals, hr8[5], P{}, NormalBinding{}) : N{},
            hr8[5].hit ? materials[hr8[5].geom_id]                         : M{}
            ),
        detail::make_surface(
            hr8[6].hit ? get_normal(normals, hr8[6], P{}, NormalBinding{}) : N{},
            hr8[6].hit ? materials[hr8[6].geom_id]                         : M{}
            ),
        detail::make_surface(
            hr8[7].hit ? get_normal(normals, hr8[7], P{}, NormalBinding{}) : N{},
            hr8[7].hit ? materials[hr8[7].geom_id]                         : M{}
            )
        );
}

#endif // VSNRAY_SIMD_ISA >= VSNRAY_SIMD_ISA_AVX



//-------------------------------------------------------------------------------------------------
// Dispatch to surface handlers with precalculated normals
//

template <
    typename HR,
    typename Primitives,
    typename Normals,
    typename Materials,
    typename Primitive,
    typename NormalBinding
    >
VSNRAY_FUNC
inline auto get_surface_with_prims_impl(
        HR const&       hr,
        Primitives      primitives,
        Normals         normals,
        Materials       materials,
        Primitive       /* */,
        NormalBinding   /* */
        ) -> decltype( get_surface_any_prim_impl(
                hr,
                normals,
                materials,
                Primitive{},
                NormalBinding{}
                ) )
{
    VSNRAY_UNUSED(primitives);
    return get_surface_any_prim_impl(
            hr,
            normals,
            materials,
            Primitive{},
            NormalBinding{}
            );
}

template <
    typename HR,
    typename Primitives,
    typename Normals,
    typename TexCoords,
    typename Materials,
    typename Textures,
    typename Primitive,
    typename NormalBinding
    >
VSNRAY_FUNC
inline auto get_surface_with_prims_impl(
        HR const&       hr,
        Primitives      primitives,
        Normals         normals,
        TexCoords       tex_coords,
        Materials       materials,
        Textures        textures,
        Primitive       /* */,
        NormalBinding   /* */
        ) -> decltype( get_surface_any_prim_impl(
                hr,
                normals,
                tex_coords,
                materials,
                textures,
                Primitive{},
                NormalBinding{}
                ) )
{
    VSNRAY_UNUSED(primitives);
    return get_surface_any_prim_impl(
            hr,
            normals,
            tex_coords,
            materials,
            textures,
            Primitive{},
            NormalBinding{}
            );
}

template <
    typename HR,
    typename Primitives,
    typename Normals,
    typename TexCoords,
    typename Materials,
    typename Colors,
    typename Textures,
    typename Primitive,
    typename NormalBinding,
    typename ColorBinding
    >
VSNRAY_FUNC
inline auto get_surface_with_prims_impl(
        HR const&       hr,
        Primitives      primitives,
        Normals         normals,
        TexCoords       tex_coords,
        Materials       materials,
        Colors          colors,
        Textures        textures,
        Primitive       /* */,
        NormalBinding   /* */,
        ColorBinding    /* */
        ) -> decltype( get_surface_any_prim_impl(
                hr,
                normals,
                tex_coords,
                materials,
                colors,
                textures,
                Primitive{},
                NormalBinding{},
                ColorBinding{}
                ) )
{
    VSNRAY_UNUSED(primitives);
    return get_surface_any_prim_impl(
            hr,
            normals,
            tex_coords,
            materials,
            colors,
            textures,
            Primitive{},
            NormalBinding{},
            ColorBinding{}
            );
}


//-------------------------------------------------------------------------------------------------
// Generic primitive / float4
//

template <
    template <typename, typename> class HR,
    typename HRP,
    typename Primitives,
    typename Normals,
    typename Materials,
    typename ...Ts,
    typename NormalBinding
    >
inline auto get_surface_with_prims_impl(
        HR<simd::ray4, HRP> const&  hr,
        Primitives                  primitives,
        Normals                     normals,
        Materials                   materials,
        generic_primitive<Ts...>    /* */,
        NormalBinding               /* */
        ) -> decltype( simd::pack(
            typename detail::decl_surface<Normals, Materials>::type{},
            typename detail::decl_surface<Normals, Materials>::type{},
            typename detail::decl_surface<Normals, Materials>::type{},
            typename detail::decl_surface<Normals, Materials>::type{}
            ) )
{
    using N = typename std::iterator_traits<Normals>::value_type;
    using M = typename std::iterator_traits<Materials>::value_type;

    auto hr4 = unpack(hr); 

    auto get_surf = [&](unsigned index)
    {
        // dispatch to scalar version of this function
        return get_surface_with_prims_impl(
                hr4[index],
                primitives,
                normals,
                materials,
                generic_primitive<Ts...>(),
                NormalBinding()
                );
    };

    return simd::pack(
            hr4[0].hit ? get_surf(0) : detail::make_surface( N(), M() ),
            hr4[1].hit ? get_surf(1) : detail::make_surface( N(), M() ),
            hr4[2].hit ? get_surf(2) : detail::make_surface( N(), M() ),
            hr4[3].hit ? get_surf(3) : detail::make_surface( N(), M() )
            );
}


//-------------------------------------------------------------------------------------------------
// Functions to deduce appropriate surface via parameter inspection
//

template <typename HR, typename Params>
VSNRAY_FUNC
inline auto get_surface_unroll_params_impl(
        HR const& hr,
        Params const& p,
        detail::has_no_colors_tag,
        detail::has_no_textures_tag
        )
    -> decltype( get_surface_with_prims_impl(
            hr,
            p.prims.begin,
            p.normals,
            p.materials,
            typename Params::primitive_type{},
            typename Params::normal_binding{}
            ) )
{
    return get_surface_with_prims_impl(
            hr,
            p.prims.begin,
            p.normals,
            p.materials,
            typename Params::primitive_type{},
            typename Params::normal_binding{}
            );
}

template <typename HR, typename Params>
VSNRAY_FUNC
inline auto get_surface_unroll_params_impl(
        HR const& hr,
        Params const& p,
        detail::has_no_colors_tag,
        detail::has_textures_tag
        )
    -> decltype( get_surface_with_prims_impl(
            hr,
            p.prims.begin,
            p.normals,
            p.tex_coords,
            p.materials,
            p.textures,
            typename Params::primitive_type{},
            typename Params::normal_binding{}
            ) )
{
    return get_surface_with_prims_impl(
            hr,
            p.prims.begin,
            p.normals,
            p.tex_coords,
            p.materials,
            p.textures,
            typename Params::primitive_type{},
            typename Params::normal_binding{}
            );
}

template <typename HR, typename Params>
VSNRAY_FUNC
inline auto get_surface_unroll_params_impl(
        HR const& hr,
        Params const& p,
        detail::has_colors_tag,
        detail::has_textures_tag
        )
    -> decltype( get_surface_with_prims_impl(
            hr,
            p.prims.begin,
            p.normals,
            p.tex_coords,
            p.materials,
            p.colors,
            p.textures,
            typename Params::primitive_type{},
            typename Params::normal_binding{},
            typename Params::color_binding{}
            ) )
{
    return get_surface_with_prims_impl(
            hr,
            p.prims.begin,
            p.normals,
            p.tex_coords,
            p.materials,
            p.colors,
            p.textures,
            typename Params::primitive_type{},
            typename Params::normal_binding{},
            typename Params::color_binding{}
            );
}


template <typename HR, typename Params>
VSNRAY_FUNC
inline auto get_surface(HR const& hr, Params const& p)
    -> decltype( get_surface_unroll_params_impl(
            hr,
            p,
            detail::has_colors<Params>{},
            detail::has_textures<Params>{}
            ) )
{
    return get_surface_unroll_params_impl(
            hr,
            p,
            detail::has_colors<Params>{},
            detail::has_textures<Params>{}
            );
}


//-------------------------------------------------------------------------------------------------
// General surface functions
//

template <typename ...Args>
VSNRAY_FUNC
inline bool has_emissive_material(surface<Args...> const& surf)
{
    VSNRAY_UNUSED(surf);
    return false;
}

template <typename N, typename T>
VSNRAY_FUNC
inline bool has_emissive_material(surface<N, emissive<T>> const& surf)
{
    VSNRAY_UNUSED(surf);
    return true;
}

template <typename N, typename ...Ms, typename ...Ts>
VSNRAY_FUNC
inline auto has_emissive_material(surface<N, generic_material<Ms...>, Ts...> const& surf)
    -> decltype( surf.material.is_emissive() )
{
    return surf.material.is_emissive();
}

template <typename N, typename ...Ms, typename ...Ts>
VSNRAY_FUNC
inline auto has_emissive_material(surface<N, simd::generic_material4<Ms...>, Ts...> const& surf)
    -> decltype( surf.material.is_emissive() )
{
    return surf.material.is_emissive();
}

} // visionaray

#endif // VSNRAY_SURFACE_INL
