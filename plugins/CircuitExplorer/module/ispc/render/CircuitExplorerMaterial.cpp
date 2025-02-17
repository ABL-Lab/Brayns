/* Copyright (c) 2015-2021, EPFL/Blue Brain Project
 * All rights reserved. Do not distribute without permission.
 * Responsible Author: Cyrille Favreau <cyrille.favreau@epfl.ch>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "CircuitExplorerMaterial.h"
#include "CircuitExplorerMaterial_ispc.h"

#include <plugin/api/MaterialUtils.h>

#include <ospray/SDK/common/Data.h>

namespace brayns
{
namespace obj
{
void CircuitExplorerMaterial::commit()
{
    if (ispcEquivalent == nullptr)
        ispcEquivalent = ispc::CircuitExplorerMaterial_create(this);

    // Opacity
    map_d = (ospray::Texture2D*)getParamObject("map_d", nullptr);
    xform_d = getTextureTransform("map_d");
    d = getParam1f("d", 1.f);

    // Diffuse color
    Kd = getParam3f("kd", ospray::vec3f(.8f));
    map_Kd = (ospray::Texture2D*)getParamObject("map_kd", nullptr);
    xform_Kd = getTextureTransform("map_kd");

    // Specular color
    Ks = getParam3f("ks", ospray::vec3f(0.f));
    map_Ks = (ospray::Texture2D*)getParamObject("map_ks", nullptr);
    xform_Ks = getTextureTransform("map_ks");

    // Specular exponent
    Ns = getParam1f("ns", 10.f);
    map_Ns = (ospray::Texture2D*)getParamObject("map_ns", nullptr);
    xform_Ns = getTextureTransform("map_ns");

    // Bump mapping
    map_Bump = (ospray::Texture2D*)getParamObject("map_bump", nullptr);
    xform_Bump = getTextureTransform("map_bump");
    rot_Bump = xform_Bump.l.orthogonal().transposed();

    // Refraction mapping
    refraction = getParam1f("refraction", 0.f);
    xform_Refraction = getTextureTransform("map_refraction");
    map_Refraction =
        (ospray::Texture2D*)getParamObject("map_refraction", nullptr);

    // Reflection mapping
    reflection = getParam1f("reflection", 0.f);
    xform_Reflection = getTextureTransform("map_reflection");
    map_Reflection =
        (ospray::Texture2D*)getParamObject("map_reflection", nullptr);

    // Light emission mapping
    a = getParam1f("a", 0.f);
    xform_a = getTextureTransform("map_a");
    map_a = (ospray::Texture2D*)getParamObject("map_a", nullptr);

    // Glossiness
    glossiness = getParam1f("glossiness", 1.f);

    // Cast simulation data
    castSimulationData = getParam(MATERIAL_PROPERTY_CAST_USER_DATA, false);

    // Shading mode
    shadingMode = static_cast<MaterialShadingMode>(
        getParam1i(MATERIAL_PROPERTY_SHADING_MODE,
                   static_cast<int>(MaterialShadingMode::none)));
    // Clipping mode
    clippingMode = static_cast<MaterialClippingMode>(
        getParam1i(MATERIAL_PROPERTY_CLIPPING_MODE,
                   static_cast<int>(MaterialClippingMode::no_clipping)));

    // User parameter
    userParameter = getParam1f(MATERIAL_PROPERTY_USER_PARAMETER, 1.f);

    ispc::CircuitExplorerMaterial_set(
        getIE(), map_d ? map_d->getIE() : nullptr,
        (const ispc::AffineSpace2f&)xform_d, d,
        map_Refraction ? map_Refraction->getIE() : nullptr,
        (const ispc::AffineSpace2f&)xform_Refraction, refraction,
        map_Reflection ? map_Reflection->getIE() : nullptr,
        (const ispc::AffineSpace2f&)xform_Reflection, reflection,
        map_a ? map_a->getIE() : nullptr, (const ispc::AffineSpace2f&)xform_a,
        a, glossiness, castSimulationData, map_Kd ? map_Kd->getIE() : nullptr,
        (const ispc::AffineSpace2f&)xform_Kd, (ispc::vec3f&)Kd,
        map_Ks ? map_Ks->getIE() : nullptr,
        (const ispc::AffineSpace2f&)xform_Ks, (ispc::vec3f&)Ks,
        map_Ns ? map_Ns->getIE() : nullptr,
        (const ispc::AffineSpace2f&)xform_Ns, Ns,
        map_Bump ? map_Bump->getIE() : nullptr,
        (const ispc::AffineSpace2f&)xform_Bump,
        (const ispc::LinearSpace2f&)rot_Bump,
        (const ispc::MaterialShadingMode&)shadingMode,
        (const ispc::MaterialClippingMode&)clippingMode, userParameter);
}

OSP_REGISTER_MATERIAL(circuit_explorer_basic, CircuitExplorerMaterial, default);
OSP_REGISTER_MATERIAL(circuit_explorer_advanced, CircuitExplorerMaterial,
                      default);
OSP_REGISTER_MATERIAL(circuit_explorer_voxelized_simulation,
                      CircuitExplorerMaterial, default);
OSP_REGISTER_MATERIAL(circuit_explorer_cell_growth, CircuitExplorerMaterial,
                      default);
OSP_REGISTER_MATERIAL(circuit_explorer_proximity_detection,
                      CircuitExplorerMaterial, default);
} // namespace obj
} // namespace brayns
