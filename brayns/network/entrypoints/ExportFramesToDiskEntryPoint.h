/* Copyright (c) 2015-2021 EPFL/Blue Brain Project
 * All rights reserved. Do not distribute without permission.
 *
 * Responsible Author: adrien.fleury@epfl.ch
 *                     nadir.romanguerrero@epfl.ch
 *
 * This file is part of Brayns <https://github.com/BlueBrain/Brayns>
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

#include <brayns/engine/FrameExporter.h>
#include <brayns/network/adapters/FrameExportdapter.h>
#include <brayns/network/entrypoint/Entrypoint.h>

namespace brayns
{
class ExportFramesToDiskEntrypoint
    : public Entrypoint<FrameExporter::ExportInfo, EmptyMessage>
{
public:
    virtual std::string getName() const override
    {
        return "export-frames-to-disk";
    }

    virtual std::string getDescription() const override
    {
        return "Export a set of frames from a simulation as image files";
    }

    virtual void onRequest(const Request& request) override
    {
        auto params = request.getParams();
        auto& engine = getApi().getEngine();
        auto& exporter = engine.getFrameExporter();
        try
        {
            exporter.startNewExport(std::move(params));
        }
        catch (const FrameExportParameterException& fpe)
        {
            throw EntrypointException(1, fpe.what());
        }
        catch (const FrameExportInProgressException&)
        {
            throw EntrypointException(2, "Frame export already in progress");
        }
        engine.triggerRender();
        request.reply(EmptyMessage());
    }
};
} // namespace brayns
