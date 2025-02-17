/* Copyright (c) 2021, EPFL/Blue Brain Project
 * All rights reserved. Do not distribute without permission.
 * Responsible Author: Nadir Roman Guerrero <nadir.romanguerrero@epfl.ch>
 *
 * This file is part of the circuit explorer for Brayns
 * <https://github.com/favreau/Brayns-UC-CircuitExplorer>
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

#include "OSPRayISPCModel.ih"

export void *uniform OSPRayISPCModel_create(void *uniform cppE)
{
  uniform OSPRayISPCModel *uniform model = uniform new uniform OSPRayISPCModel;
  model->super.cppEquivalent     = cppE;
  model->super.embreeSceneHandle = NULL;
  model->super.geometry          = NULL;
  model->super.volumes           = NULL;
  model->simEnabled              = true;
  model->simOffset               = 0;
  return (void *uniform)model;
}

export void OSPRayISPCModel_init(void *uniform _model,
                                 uniform bool simEnabled,
                                 uniform uint64 simOffset)
{
    uniform OSPRayISPCModel *uniform model = (uniform OSPRayISPCModel *uniform)_model;
    model->simEnabled = simEnabled;
    model->simOffset = simOffset;
}
