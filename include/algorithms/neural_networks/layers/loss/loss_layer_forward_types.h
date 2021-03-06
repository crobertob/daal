/* file: loss_layer_forward_types.h */
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

/*
//++
//  Implementation of the forward loss layer types.
//--
*/

#ifndef __NEURAL_NETWORKS__LOSS_LAYER_FORWARD_TYPES_H__
#define __NEURAL_NETWORKS__LOSS_LAYER_FORWARD_TYPES_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "data_management/data/homogen_tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer_forward_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace loss
{
/**
 * \brief Contains classes for the forward loss layer
 */
namespace forward
{
/**
 * <a name="DAAL-ENUM-ALGORITHMS__NEURAL_NETWORKS__LAYERS__FORWARD__INPUTID"></a>
 * Available identifiers of input objects for the loss layer algorithm
 */
enum InputId
{
    data = 0,       /*!< Input data */
    weights = 1,    /* Weights of the neural network layer */
    biases = 2,      /* Biases of the neural network layer */
    groundTruth = 4  /* Groung truth for the loss layer */
};
/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__LOSS__FORWARD__INPUT"></a>
 * \brief %Input objects for the forward loss layer
 */
class Input : public layers::forward::Input
{
public:
    /** Default constructor */
    Input(size_t nElements = 5) : layers::forward::Input(nElements) {};

    /**
     * Returns an input object for the forward loss layer
     */
    using layers::forward::Input::get;

    /**
     * Sets an input object for the forward loss layer
     */
    using layers::forward::Input::set;

    /**
     * Returns input Tensor of the loss layer algorithm
     * \param[in] id    Identifier of the input tensor
     * \return          %Input tensor that corresponds to the given identifier
     */
    services::SharedPtr<data_management::Tensor> get(forward::InputId id) const
    {
        return services::staticPointerCast<data_management::Tensor, data_management::SerializationIface>(Argument::get(id));
    }

    /**
     * Sets input for the loss layer algorithm
     * \param[in] id    Identifier of the input object
     * \param[in] ptr   Pointer to the object
     */
    void set(InputId id, const services::SharedPtr<data_management::Tensor> &ptr)
    {
        Argument::set(id, ptr);
    }

    /**
     * Returns dimensions of weights tensor
     * \return Dimensions of weights tensor
     */
    virtual const services::Collection<size_t> getWeightsSizes(const layers::Parameter *parameter) const DAAL_C11_OVERRIDE
    {
        return services::Collection<size_t>();
    }

    /**
     * Returns dimensions of biases tensor
     * \return Dimensions of biases tensor
     */
    virtual const services::Collection<size_t> getBiasesSizes(const layers::Parameter *parameter) const DAAL_C11_OVERRIDE
    {
        return services::Collection<size_t>();
    }

    virtual ~Input() {}
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__LOSS__RESULT"></a>
 * \brief Provides methods to access the result obtained with the compute() method
 *        of the forward loss layer
 */
class Result : public layers::forward::Result
{
public:
    /** Default constructor */
    Result() : layers::forward::Result() {};
    virtual ~Result() {};

    /**
     * Returns the result of the forward loss layer
     */
    using layers::forward::Result::get;

    /**
     * Sets the result of the forward loss layer
     */
    using layers::forward::Result::set;

    /**
     * Checks the result of the forward loss layer
     * \param[in] input   %Input object for the loss layer
     * \param[in] par     %Parameter of the loss layer
     * \param[in] method  Computation method
     */
    void check(const daal::algorithms::Input *input, const daal::algorithms::Parameter *par, int method) const DAAL_C11_OVERRIDE
    {
        const Input *in = static_cast<const Input *>(input);

        if (!data_management::checkTensor(in->get(layers::forward::data).get(), this->_errors.get(), strData())) { return; }

        if (!data_management::checkTensor(get(layers::forward::value).get(), this->_errors.get(), strValue())) { return; }
    }

    /**
     * Allocates memory to store the result of the forward loss layer
     * \param[in] input Pointer to an object containing the input data
     * \param[in] method Computation method for the loss layer
     * \param[in] parameter %Parameter of the forward loss layer
     */
    template <typename algorithmFPType>
    void allocate(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, const int method)
    {
        const layers::forward::Input *in = static_cast<const layers::forward::Input * >(input);

        services::Collection<size_t> valueDim(1);
        valueDim[0] = 1;
        Argument::set(layers::forward::value, services::SharedPtr<data_management::SerializationIface>(
                          new data_management::HomogenTensor<algorithmFPType>(valueDim, data_management::Tensor::doAllocate)));
        Argument::set(layers::forward::resultForBackward, services::SharedPtr<LayerData>(new LayerData()));
    }

    /**
     * Returns dimensions of value tensor
     * \return Dimensions of value tensor
     */
    virtual const services::Collection<size_t> getValueSize(const services::Collection<size_t> &inputSize,
            const daal::algorithms::Parameter *par, const int method) const DAAL_C11_OVERRIDE
    {
        return inputSize;
    }
};
} // namespace interface1
using interface1::Input;
using interface1::Result;
} // namespace forward
} // namespace loss
} // namespace layers
} // namespace neural_networks
} // namespace algorithm
} // namespace daal
#endif
