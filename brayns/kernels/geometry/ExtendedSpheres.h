/* Copyright (c) 2011-2015, EPFL/Blue Brain Project
 *                     Cyrille Favreau <cyrille.favreau@epfl.ch>
 *
 * This file is part of BRayns
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

#pragma once

#include "ospray/geometry/Geometry.h"

namespace brayns
{
struct ExtendedSpheres : public ospray::Geometry
{
    virtual std::string toString() const { return "hbp::ExtendedSpheres"; }
    virtual void finalize(ospray::Model *model);

    float radius;
    int32 materialID;

    size_t numExtendedSpheres;
    size_t bytesPerExtendedSphere;
    int64 offset_center;
    int64 offset_radius;
    int64 offset_frame;
    int64 offset_materialID;

    ospray::Ref<ospray::Data> data;
    ospray::Ref<ospray::Data> materialList;

    ExtendedSpheres();

private:
    std::vector<void *> ispcMaterials_;

};

} // ::brayns

