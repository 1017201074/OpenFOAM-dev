/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "constantAbsorptionEmission.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    namespace radiation
    {
        defineTypeNameAndDebug(constantAbsorptionEmission, 0);

        addToRunTimeSelectionTable
        (
            absorptionEmissionModel,
            constantAbsorptionEmission,
            dictionary
        );
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::radiation::constantAbsorptionEmission::constantAbsorptionEmission
(
    const dictionary& dict,
    const fvMesh& mesh
)
:
    absorptionEmissionModel(dict, mesh),
    coeffsDict_(dict.optionalSubDict(typeName + "Coeffs")),
    a_("absorptivity", dimless/dimLength, coeffsDict_),
    e_("emissivity", dimless/dimLength, coeffsDict_),
    E_("E", dimMass/dimLength/pow3(dimTime), coeffsDict_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::radiation::constantAbsorptionEmission::~constantAbsorptionEmission()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField>
Foam::radiation::constantAbsorptionEmission::aCont(const label bandI) const
{
    return volScalarField::New
    (
        "a",
        mesh_,
        a_
    );
}


Foam::tmp<Foam::volScalarField>
Foam::radiation::constantAbsorptionEmission::eCont(const label bandI) const
{
    return volScalarField::New
    (
        "e",
        mesh_,
        e_
    );
}


Foam::tmp<Foam::volScalarField>
Foam::radiation::constantAbsorptionEmission::ECont(const label bandI) const
{
    return volScalarField::New
    (
        "E",
        mesh_,
        E_
    );
}


// ************************************************************************* //
