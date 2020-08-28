#include "pch.h"
#include "Transform.h"


namespace nc 
{
	std::istream& nc::operator>>(std::istream& stream, Transform& t)
	{
		stream >> t.position;

		std::string line;
		std::getline(stream, line);
		t.scale = stof(line);
		
		std::getline(stream, line);
		t.angle = stof(line);

		return stream;
	}

	void Transform::Update()
	{
		nc::Matrix33 mxs;
		mxs.Scale(scale);

		nc::Matrix33 mxr;
		mxr.rotate(angle);

		nc::Matrix33 mxt;
		mxt.translate(position);

		matrix = mxs * mxr * mxt;
	}

	void Transform::Update(const Matrix33& mx)
	{
		nc::Matrix33 mxs;
		mxs.Scale(scale);

		nc::Matrix33 mxr;
		mxr.rotate(angle);

		nc::Matrix33 mxt;
		mxt.translate(position);

		matrix = mxs * mxr * mxt * mx;
	}
}
