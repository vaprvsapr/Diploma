#include "pch.h"

#include <iostream>
#include "C:\Users\Mi\source\repos\Diploma\Diploma\Structures.h"
#include "C:\Users\Mi\source\repos\Diploma\Diploma\GetPixelCoordinate.h"
#include "C:\Users\Mi\source\repos\Diploma\Diploma\Projection.h"

namespace TestGetPixelCoorinate
{
	TEST(GetPixelCoordinate, TopLeft)
	{
		Camera cam(
			{},
			Coordinate3D{ 0, 0, 100 },
			EulerAngles{ 0, 0, 0 },
			MatrixSize{ 1, 1 },
			FieldOfView{ 1.57 / 2, 1.57 / 2 }
		);
		cam.image_size = { 2990, 4500 };
		cam.focal_length = cam.matrix_size.width / 2 /
			(tan(cam.field_of_view.horizontal / 2));
		Coordinate3D pixel_coordinate = GetPixelCoordinate(cam, { 1, 1 });
		EXPECT_TRUE((pixel_coordinate.x - 1.2) < 0.01);
		EXPECT_TRUE((pixel_coordinate.y - 0.5) < 0.01);
		EXPECT_TRUE((pixel_coordinate.z - 100.5) < 0.01);
	}

	TEST(GetPixelCoordinate, TopRight)
	{
		Camera cam(
			{},
			Coordinate3D{ 0, 0, 100 },
			EulerAngles{ 0, 0, 0 },
			MatrixSize{ 1, 1 },
			FieldOfView{ 1.57 / 2, 1.57 / 2 }
		);
		cam.image_size = { 2990, 4500 };
		cam.focal_length = cam.matrix_size.width / 2 /
			(tan(cam.field_of_view.horizontal / 2));
		Coordinate3D pixel_coordinate =
			GetPixelCoordinate(cam, { 1, cam.image_size.width });
		EXPECT_TRUE((pixel_coordinate.x - 1.2) < 0.01);
		EXPECT_TRUE((pixel_coordinate.y + 0.5) < 0.01);
		EXPECT_TRUE((pixel_coordinate.z - 100.5) < 0.01);
	}

	TEST(GetPixelCoordinate, BottomLeft)
	{
		Camera cam(
			{},
			Coordinate3D{ 0, 0, 100 },
			EulerAngles{ 0, 0, 0 },
			MatrixSize{ 1, 1 },
			FieldOfView{ 1.57 / 2, 1.57 / 2 }
		);
		cam.image_size = { 2990, 4500 };
		cam.focal_length = cam.matrix_size.width / 2 /
			(tan(cam.field_of_view.horizontal / 2));
		Coordinate3D pixel_coordinate =
			GetPixelCoordinate(cam,
				{ cam.image_size.height, 0 });
		EXPECT_TRUE((pixel_coordinate.x - 1.2) < 0.01);
		EXPECT_TRUE((pixel_coordinate.y - 0.5) < 0.01);
		EXPECT_TRUE((pixel_coordinate.z - 99.5) < 0.01);
	}

	TEST(GetPixelCoordinate, BottomRight)
	{
		Camera cam(
			{},
			Coordinate3D{ 0, 0, 100 },
			EulerAngles{ 0, 0, 0 },
			MatrixSize{ 1, 1 },
			FieldOfView{ 1.57 / 2, 1.57 / 2 }
		);
		cam.image_size = { 2990, 4500 };
		cam.focal_length = cam.matrix_size.width / 2 /
			(tan(cam.field_of_view.horizontal / 2));
		Coordinate3D pixel_coordinate =
			GetPixelCoordinate(cam,
				{ cam.image_size.height, cam.image_size.width });
		EXPECT_TRUE((pixel_coordinate.x - 1.2) < 0.01);
		EXPECT_TRUE((pixel_coordinate.y + 0.5) < 0.01);
		EXPECT_TRUE((pixel_coordinate.z - 99.5) < 0.01);
	}

	TEST(GetPixelCoordinate, Random)
	{
		Camera cam(
			{},
			Coordinate3D{ 0, 0, 100 },
			EulerAngles{ 0, 0, 0 },
			MatrixSize{ 1, 1 },
			FieldOfView{ 1.57 / 2, 1.57 / 2 }
		);
		cam.image_size = { 2990, 4500 };
		cam.focal_length = cam.matrix_size.width / 2 /
			(tan(cam.field_of_view.horizontal / 2));
		Coordinate3D pixel_coordinate =
			GetPixelCoordinate(cam, { 1124, 789 });
		EXPECT_TRUE((pixel_coordinate.x - 1.2) < 0.01);
		EXPECT_TRUE((pixel_coordinate.y - 0.324) < 0.01);
		EXPECT_TRUE((pixel_coordinate.z - 100.124) < 0.01);
	}
}

namespace TestProjection
{
	TEST(Projection, TopLeft)
	{
		Camera cam(
			{},
			Coordinate3D{ 0, 0, 100 },
			EulerAngles{ 0, 0, 0 },
			MatrixSize{ 1, 1 },
			FieldOfView{ 1.57 / 2, 1.57 / 2 }
		);
		cam.image_size = { 2990, 4500 };
		cam.focal_length = cam.matrix_size.width / 2 /
			(tan(cam.field_of_view.horizontal / 2));
		Coordinate2D projection =
			Projection(cam,
				GetPixelCoordinate(cam, { 0, 0 }));
		EXPECT_TRUE((projection.x + 241.557) < 0.01);
		EXPECT_TRUE((projection.y + 100) < 0.01);
	}

	TEST(Projection, TopRight)
	{
		Camera cam(
			{},
			Coordinate3D{ 0, 0, 100 },
			EulerAngles{ 0, 0, 0 },
			MatrixSize{ 1, 1 },
			FieldOfView{ 1.57 / 2, 1.57 / 2 }
		);
		cam.image_size = { 2990, 4500 };
		cam.focal_length = cam.matrix_size.width / 2 /
			(tan(cam.field_of_view.horizontal / 2));
		Coordinate2D projection =
			Projection(cam,
				GetPixelCoordinate(cam,
					{ 0, cam.image_size.width }));
		EXPECT_TRUE((projection.x + 241.557) < 0.01);
		EXPECT_TRUE((projection.y - 100) < 0.01);
	}

	TEST(Projection, BottomLeft)
	{
		Camera cam(
			{},
			Coordinate3D{ 0, 0, 100 },
			EulerAngles{ 0, 0, 0 },
			MatrixSize{ 1, 1 },
			FieldOfView{ 1.57 / 2, 1.57 / 2 }
		);
		cam.image_size = { 2990, 4500 };
		cam.focal_length = cam.matrix_size.width / 2 /
			(tan(cam.field_of_view.horizontal / 2));
		Coordinate2D projection =
			Projection(cam,
				GetPixelCoordinate(cam,
					{ cam.image_size.height, 0 }));
		EXPECT_TRUE((projection.x - 241.557) < 0.01);
		EXPECT_TRUE((projection.y - 100) < 0.01);
	}

	TEST(Projection, BottomRight)
	{
		Camera cam(
			{},
			Coordinate3D{ 0, 0, 100 },
			EulerAngles{ 0, 0, 0 },
			MatrixSize{ 1, 1 },
			FieldOfView{ 1.57 / 2, 1.57 / 2 }
		);
		cam.image_size = { 2990, 4500 };
		cam.focal_length = cam.matrix_size.width / 2 /
			(tan(cam.field_of_view.horizontal / 2));
		Coordinate2D projection =
			Projection(cam,
				GetPixelCoordinate(cam,
					{ cam.image_size.height, cam.image_size.width }));
		EXPECT_TRUE((projection.x - 241.557) < 0.01);
		EXPECT_TRUE((projection.y + 100) < 0.01);
	}

	TEST(Projection, Random)
	{
		Camera cam(
			{},
			Coordinate3D{ 0, 0, 100 },
			EulerAngles{ 0, 0, 0 },
			MatrixSize{ 1, 1 },
			FieldOfView{ 1.57 / 2, 1.57 / 2 }
		);
		cam.image_size = { 2990, 4500 };
		cam.focal_length = cam.matrix_size.width / 2 /
			(tan(cam.field_of_view.horizontal / 2));
		Coordinate2D projection =
			Projection(cam,
				GetPixelCoordinate(cam,
					{ 1593, 43 }));
		EXPECT_TRUE((projection.x - 3684.99) < 0.01);
		EXPECT_TRUE((projection.y - 1496.36) < 0.01);
	}
}

namespace TestRotate
{
	TEST(Rotate, Rotate)
	{
		double angle = 3.141592 / 2;

		Coordinate3D
			nx = { 1, 0, 0 },
			ny = { 0, 1, 0 },
			nz = { 0, 0, 1 },
			rnx = Rotate(X, nx, angle),
			rny = Rotate(X, ny, angle),
			rnz = Rotate(X, nz, -angle);

		EXPECT_TRUE((nx.x - rnx.x) < 0.001);
		EXPECT_TRUE((nx.y - rnx.z) < 0.001);
		EXPECT_TRUE((nx.z - rnx.z) < 0.001);

		EXPECT_TRUE((nz.x - rny.x) < 0.001);
		EXPECT_TRUE((nz.y - rny.z) < 0.001);
		EXPECT_TRUE((nz.z - rny.z) < 0.001);

		EXPECT_TRUE((ny.x - rnz.x) < 0.001);
		EXPECT_TRUE((ny.y - rnz.y) < 0.001);
		EXPECT_TRUE((ny.z - rnz.z) < 0.001);
	}

	TEST(Roate, RotateZ)
	{
		double angle = 3.141592 / 2;

		Coordinate2D
			nx = { 1, 0 },
			ny = { 0, 1 },
			v = { 1, 1 },
			rnx = RotateZ(nx, angle),
			rny = RotateZ(ny, 3 * angle),
			rv = RotateZ(v, angle / 2);

		EXPECT_TRUE((ny.x - rnx.x) < 0.001);


	}
}