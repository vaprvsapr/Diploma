#pragma once

#include "Structures.h"
#include "GetPixelCoordinate.h"
#include "Projection.h"


pair<vector<Coordinate3D>, vector<EulerAngles>> CreateTackTrajectory(
	Coordinate2D initial_point,
	Size2D delta,
	Size2D overlap, // {0.2, 0.3}
	double pitch,
	double height,
	double horizontal_field_of_view,
	ImageSize image_size
)
{
	Camera camera{
		{0, 0, height},
		{0, pitch, 0},
		horizontal_field_of_view,
		image_size
	};

	Coordinate3D
		top_left_3d = GetPixelCoordinate(camera,
			{ 0, 0 }),
		top_right_3d = GetPixelCoordinate(camera,
			{ 0, camera.image_size.width }),
		bottom_left_3d = GetPixelCoordinate(camera,
			{ camera.image_size.height, 0 }),
		bottom_right_3d = GetPixelCoordinate(camera,
			{ camera.image_size.height,
			camera.image_size.width });

	Coordinate2D
		top_left = Projection(camera.position, top_left_3d),
		top_right = Projection(camera.position, top_right_3d),
		bottom_left = Projection(camera.position, bottom_left_3d),
		bottom_right = Projection(camera.position, bottom_right_3d);

	Size2D rectangle_size = {
		abs(top_left.x - bottom_left.x),
		abs(bottom_left.y - bottom_right.y)
	};
	cout << "rectangle_size:" << rectangle_size.height 
		<< ", " << rectangle_size.width << endl;

	Size2D shift = {
		rectangle_size.height * (1 - overlap.height),
		rectangle_size.width * (1 - overlap.width)
	};

	cout << "shift:" << shift.height << ", " << shift.width << endl;

	size_t n_height = ceil(delta.height / shift.height);
	size_t n_width = ceil(delta.width / shift.width);

	cout << "n:" << n_height << ", " << n_width << endl;

	vector<Coordinate3D> positions;
	vector<EulerAngles> orientations;

	for (size_t i = 0; i < n_height; i++)
	{
		for (size_t j = 0; j < n_width; j++)
		{

				double x = i * shift.height;
				double y = j * shift.width;

				positions.push_back({
					x + initial_point.x + rectangle_size.height / 2 - height / tan(pitch),
					y + initial_point.y + rectangle_size.width / 2,
					height });

				orientations.push_back({ 0, pitch, 0 });
		}
	}
	return make_pair(positions, orientations);
}
