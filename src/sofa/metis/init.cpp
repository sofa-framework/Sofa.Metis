/******************************************************************************
*                 SOFA, Simulation Open-Framework Architecture                *
*                    (c) 2006 INRIA, USTL, UJF, CNRS, MGH                     *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#include <sofa/component/linearsolver/direct/EigenSolverFactory.h>
#include <sofa/metis/init.h>

#include <sofa/core/ObjectFactory.h>
using sofa::core::ObjectFactory;

#include <Eigen/MetisSupport>

namespace sofa::metis
{
    extern "C" {
        SOFA_METIS_API void initExternalModule();
        SOFA_METIS_API const char* getModuleName();
        SOFA_METIS_API const char* getModuleVersion();
        SOFA_METIS_API const char* getModuleDescription();
        SOFA_METIS_API const char* getModuleComponentList();
    }


    template<class EigenSolverFactory, class Scalar>
    void registerOrderingMethods()
    {
        EigenSolverFactory::template registerSolver<Eigen::MetisOrdering<int>, Scalar >("Metis");
    }

    template<class Scalar>
    void registerOrderingMethods()
    {
        registerOrderingMethods<component::linearsolver::direct::MainSimplicialLDLTFactory, Scalar>();
        registerOrderingMethods<component::linearsolver::direct::MainSimplicialLLTFactory, Scalar>();
        registerOrderingMethods<component::linearsolver::direct::MainLUFactory, Scalar>();
        registerOrderingMethods<component::linearsolver::direct::MainQRFactory, Scalar>();
    }

    void init()
    {
        static bool first = true;
        if (first)
        {
            registerOrderingMethods<float>();
            registerOrderingMethods<double>();

            first = false;
        }
    }

    //Here are just several convenient functions to help user to know what contains the plugin

    void initExternalModule()
    {
        init();
    }

    const char* getModuleName()
    {
        return sofa_tostring(SOFA_TARGET);
    }

    const char* getModuleDescription()
    {
        return "";
    }

    const char* getModuleComponentList()
    {
        /// string containing the names of the classes provided by the plugin
        static std::string classes = ObjectFactory::getInstance()->listClassesFromTarget(sofa_tostring(SOFA_TARGET));
        return classes.c_str();
    }

}
