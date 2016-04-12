/* file: prelu_layer_backward_kernel.h */
/*******************************************************************************
* Copyright 2014-2016 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

//++
//  Implementation of prelu calculation functions.
//--


#ifndef __PRELU_LAYER_BACKWARD_KERNEL_H__
#define __PRELU_LAYER_BACKWARD_KERNEL_H__

#include "neural_networks/layers/prelu/prelu_layer.h"
#include "neural_networks/layers/prelu/prelu_layer_types.h"
#include "kernel.h"

using namespace daal::data_management;
using namespace daal::services;

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace prelu
{
namespace backward
{
namespace internal
{

/**
 *  \brief Kernel for prelu calculation
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class PReLUKernel : public Kernel
{
public:
    void compute(const prelu::backward::Input *input, const prelu::Parameter *parameter,
                 prelu::backward::Result *result);
};

} // internal
} // backward
} // prelu
} // layers
} // neural_networks
} // algorithms
} // daal

#endif