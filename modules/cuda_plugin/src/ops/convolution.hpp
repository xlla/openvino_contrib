// Copyright (C) 2018-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <cuda_operation_base.hpp>
#include <memory>
#include <ngraph/op/convolution.hpp>

#include "convolution_components.hpp"

namespace CUDAPlugin {

class ConvolutionOp : public OperationCuDnn {
public:
    using NodeOp = ngraph::op::v1::Convolution;
    ConvolutionOp(const CreationContext& context,
                  const NodeOp& node,
                  IndexCollection&& inputIds,
                  IndexCollection&& outputIds);
    void Execute(const InferenceRequestContext& context,
                 Inputs inputTensors,
                 Outputs outputTensors,
                 const Workbuffers&) const override;
    WorkbufferRequest GetWorkBufferRequest() const override;

    void InitSharedImmutableWorkbuffers(const IOperationExec::Buffers&) override {}
    const WorkbufferIds& GetWorkbufferIds() const override;
    WorkbufferStatus SetWorkbufferIds(WorkbufferIds&& workbufferIds) override;

    using ArgIndices = Convolution::Details::ConvArgIndices;

private:
    void CreateImpl(const CreationContext& context, const NodeOp& node);

private:
    std::unique_ptr<IOperationExec> impl_;
};

}  // namespace CUDAPlugin
