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
		abs(bottom_left.y - bottom_right.y) / 2 + abs(top_left.y - top_right.y) / 2
	};

	Size2D shift = {
		rectangle_size.height * (1 - overlap.height),
		rectangle_size.width * (1 - overlap.width)
	};

	size_t n_height = ceil(delta.height / shift.height);
	size_t n_width = ceil(delta.width / shift.width);

	Size2D alignment = {
		(rectangle_size.height + (n_height - 1) * shift.height - delta.height) / 2,
		(rectangle_size.width + (n_width - 1) * shift.width - delta.width) / 2
	};

	vector<Coordinate3D> positions;
	vector<EulerAngles> orientations;

	for (size_t j = 0; j < n_width; j++)
	{
		for (size_t i = 0; i < n_height; i++)
		{
			if ((j % 2) == 0)
			{
				positions.push_back({
					initial_point.x + i * shift.height + 
					height / tan(pitch) - bottom_left.x - alignment.height - height / tan(pitch),
					initial_point.y + j * shift.width + 
					rectangle_size.width / 2 - alignment.width,
					height
					});
				orientations.push_back({ 0, pitch, 0 });
			}
			if ((j % 2) == 1)
			{
				positions.push_back({
					initial_point.x + delta.height - i * shift.height -
					height / tan(pitch) + bottom_left.x + alignment.height + height / tan(pitch),
					initial_point.y + j * shift.width +
					rectangle_size.width / 2 - alignment.width,
					height
					});
				orientations.push_back({ 0, pitch, 3.141592 });
			}
		}
	}
	return make_pair(positions, orientations);
}

pair<vector<Coordinate3D>, vector<EulerAngles>> CreateTrajectoryForGeoscan201(
	Coordinate2D initial_point,
	Size2D delta,
	Size2D overlap,
	double horizontal_field_of_view,
	ImageSize image_size,
	size_t max_frame_rate,
	double spatial_resolution
)
{
	pair<double, double> speed_range = { 20, 36 }; // горизонтальная скорость в м/с
	double height =
		spatial_resolution / (tan(horizontal_field_of_view / 2) -
			tan(horizontal_field_of_view / 2 -
				horizontal_field_of_view / image_size.width));
	height = height * 0.9; // закладываем дополнительную точность
	height = floor(height); // округляем до целого

	cout << "flight height: " << height << endl;

	Camera camera{
	{0, 0, height},
	{0, 3.141592 / 2, 0}, // надир
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
		abs(top_left.y - top_right.y)
	};
	cout << "rectangle_size: " << rectangle_size.height << " " << rectangle_size.width << endl;

	Size2D desired_shift = {
	rectangle_size.height * (1 - overlap.height),
	rectangle_size.width * (1 - overlap.width)
	};

	double speed = 0;
	size_t min_frame_rate = max_frame_rate;
	for (size_t frame_rate = max_frame_rate; frame_rate > 0; frame_rate--)
	{
		pair<double, double> shift_range = {
			speed_range.first / frame_rate,
			speed_range.second / frame_rate };
		if ((desired_shift.height > shift_range.first))
		{
			min_frame_rate = frame_rate;
			speed = desired_shift.height / frame_rate;
			speed = speed > speed_range.second ? speed_range.second : speed;
		}
	}

	//speed = floor(speed * 100) / 100;

	Size2D shift = {
		speed * min_frame_rate,
		desired_shift.width
	};

	cout << "speed: " << speed << endl;
	cout << "frame_rate: " << min_frame_rate << endl;

	size_t n_height = ceil(delta.height / shift.height);
	size_t n_width = ceil(delta.width / shift.width);

	Size2D alignment = {
		(n_height * shift.height - delta.height) / 2,
		(n_width * shift.width - delta.width) / 2
	};

	vector<Coordinate3D> positions;
	vector<EulerAngles> orientations;

	for (size_t j = 0; j < n_width; j++)
	{
		for (size_t i = 0; i < n_height; i++)
		{
			if ((j % 2) == 0)
			{
				positions.push_back({
					initial_point.x + i * shift.height - 
					bottom_left.x - alignment.height,
					initial_point.y + j * shift.width +
					rectangle_size.width / 2 - alignment.width,
					height
					});
				orientations.push_back({ 0, 3.141592 / 2, 0 });
			}
			if ((j % 2) == 1)
			{
				positions.push_back({
					initial_point.x + delta.height - i * shift.height + 
					bottom_left.x + alignment.height,
					initial_point.y + j * shift.width +
					rectangle_size.width / 2 - alignment.width,
					height
					});
				orientations.push_back({ 0, 3.141592 / 2, 3.141592 });
			}
		}
	}
	return make_pair(positions, orientations);
}