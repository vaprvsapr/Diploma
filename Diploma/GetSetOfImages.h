#pragma once

#include "Structures.h"
#include "GetCamera.h"
#include "WriteCamera.h"

void GetSetOfImages(
	ReferenceImage reference_image,
	vector<Coordinate3D> positions,
	vector<EulerAngles> orientations,
	double horizontal_field_of_view,
	ImageSize image_size,
	const string& directory
)
{
	if (positions.size() != orientations.size())
	{
		throw logic_error(
			"positions.size() != orientations.size()");
	}

	for (size_t i = 0; i < positions.size(); i++)
	{
		auto camera = GetCamera(
			reference_image,
			Camera{
				positions[i],
				orientations[i],
				horizontal_field_of_view,
				image_size
			}
		);

		WriteCameraWithIndex(camera, directory, i);
	}
}
