
i=0;

function count()
	local res = i;
	i=i+2;
	return res;
end

path1=
{
	type="hsplinecurve",
	offset={x=500,y=0},
	{time=count(),x=100,y=1000},
	{time=count(),x=100,y=1000},
	{time=count(),x=200,y=800},
	{time=count(),x=300,y=700},
	{time=count(),x=200,y=600},
	{time=count(),x=100,y=500},
	{time=count(),x=200,y=400},
	{time=count(),x=300,y=300},
	{time=count(),x=200,y=200},
	{time=count(),x=100,y=100},
	{time=count(),x=100,y=100},
	{time=count(),x=100,y=300},
}


i=0;
path2=
{
	type="hsplinecurve",
	offset={x=200,y=0},
	{time=count(),x=100,y=1000},
	{time=count(),x=100,y=1000},
	{time=count(),x=200,y=800},
	{time=count(),x=300,y=700},
	{time=count(),x=200,y=600},
	{time=count(),x=100,y=500},
	{time=count(),x=200,y=400},
	{time=count(),x=300,y=300},
	{time=count(),x=200,y=200},
	{time=count(),x=100,y=100},
	{time=count(),x=100,y=100},
	{time=count(),x=100,y=300},
}

i=0;
path3=
{
	type="hsplinecurve",
	offset={x=700,y=0},
	{time=count(),x=100,y=1000},
	{time=count(),x=100,y=1000},
	{time=count(),x=200,y=800},
	{time=count(),x=300,y=700},
	{time=count(),x=200,y=600},
	{time=count(),x=100,y=500},
	{time=count(),x=200,y=400},
	{time=count(),x=300,y=300},
	{time=count(),x=200,y=200},
	{time=count(),x=100,y=100},
	{time=count(),x=100,y=100},
	{time=count(),x=100,y=300},
}

i=0;
path4=
{
	type="hsplinecurve",
	offset={x=1000,y=0},
	{time=count(),x=100,y=1000},
	{time=count(),x=100,y=1000},
	{time=count(),x=200,y=800},
	{time=count(),x=300,y=700},
	{time=count(),x=200,y=600},
	{time=count(),x=100,y=500},
	{time=count(),x=200,y=400},
	{time=count(),x=300,y=300},
	{time=count(),x=200,y=200},
	{time=count(),x=100,y=100},
	{time=count(),x=100,y=100},
	{time=count(),x=100,y=300},
}

i=0;
path5=
{
	type="hsplinecurve",
	offset={x=0,y=0},
	{time=count(),x=100,y=1000},
	{time=count(),x=100,y=1000},
	{time=count(),x=200,y=800},
	{time=count(),x=300,y=700},
	{time=count(),x=200,y=600},
	{time=count(),x=100,y=500},
	{time=count(),x=200,y=400},
	{time=count(),x=300,y=300},
	{time=count(),x=200,y=200},
	{time=count(),x=100,y=100},
	{time=count(),x=100,y=100},
	{time=count(),x=100,y=300},
}

i=0;
path6=
{
	type="hsplinecurve",
	offset={x=1200,y=0},
	{time=count(),x=100,y=1000},
	{time=count(),x=100,y=1000},
	{time=count(),x=200,y=800},
	{time=count(),x=300,y=700},
	{time=count(),x=200,y=600},
	{time=count(),x=100,y=500},
	{time=count(),x=200,y=400},
	{time=count(),x=300,y=300},
	{time=count(),x=200,y=200},
	{time=count(),x=100,y=100},
	{time=count(),x=100,y=100},
	{time=count(),x=100,y=300},
}

straight1=
{
	type="straight",
	velocity=200,
	polygon=
	{
		{x=1,y=1},
		{x=1,y=50},
	}
}

nway1=
{
	type="nway",
	num=40,
	RadiationAngle=40,
}

tower1=
{
	x=-1,
	y=-1,
	trajectory=nway1,
	behavior=straight1,
	type="ray",
	atk=50,
	atkspeed=0.2,
	ballpic=103,
	picpos={w=1,h=1,x=1,y=1},
	angle=0,
	--
	ballw=5,
	ballh=50,
}

plane1 =
{
	path = path1,
	w=100,
	h=100,
	texture=102,
	tower=
	{
		tower1
	},
	polygon=
	{
		{x=-50,y=-50},
		{x=0,y=50},
		{x=50,y=-50},
	},
}

plane2 =
{
	path = path2,
	w=100,
	h=100,
	texture=102,
	tower=
	{
		tower1
	},
	polygon=
	{
		{x=-50,y=-50},
		{x=0,y=50},
		{x=50,y=-50},
	},
}
plane3 =
{
	path = path3,
	w=100,
	h=100,
	texture=102,
	tower=
	{
		tower1
	},
	polygon=
	{
		{x=-50,y=-50},
		{x=0,y=50},
		{x=50,y=-50},
	},
}
plane4 =
{
	path = path4,
	w=100,
	h=100,
	texture=102,
	tower=
	{
		tower1
	},
	polygon=
	{
		{x=-50,y=-50},
		{x=0,y=50},
		{x=50,y=-50},
	},
}
plane5 =
{
	path = path5,
	w=100,
	h=100,
	texture=102,
	tower=
	{
		tower1
	},
	polygon=
	{
		{x=-50,y=-50},
		{x=0,y=50},
		{x=50,y=-50},
	},
}
plane6 =
{
	path = path6,
	w=100,
	h=100,
	texture=102,
	tower=
	{
		tower1
	},
	polygon=
	{
		{x=-50,y=-50},
		{x=0,y=50},
		{x=50,y=-50},
	},
}


stage =
{
	{
		time=3.0,
		plane=plane1
	},

	{
		time=7.0,
		plane=plane2
	},
	{
		time=7.0,
		plane=plane3
	},

	{
		time=11.0,
		plane=plane1
	},
	{
		time=11.0,
		plane=plane2
	},
	{
		time=11.0,
		plane=plane3
	},

	{
		time=14.0,
		plane=plane1
	},
	{
		time=14.0,
		plane=plane2
	},
	{
		time=14.0,
		plane=plane3
	},
	{
		time=16.0,
		plane=plane4
	},

	{
		time=20.0,
		plane=plane1
	},
	{
		time=20.0,
		plane=plane2
	},
	{
		time=20.0,
		plane=plane3
	},
	{
		time=20.0,
		plane=plane4
	},
	{
		time=20.0,
		plane=plane5
	},

	{
		time=25.0,
		plane=plane1
	},
	{
		time=24.0,
		plane=plane2
	},
	{
		time=25.0,
		plane=plane3
	},
	{
		time=24.0,
		plane=plane4
	},
	{
		time=25.0,
		plane=plane5
	},

	{
		time=30.0,
		plane=plane1
	},
	{
		time=30.0,
		plane=plane2
	},
	{
		time=30.0,
		plane=plane3
	},
	{
		time=30.0,
		plane=plane4
	},
	{
		time=30.0,
		plane=plane5
	},
	{
		time=30.0,
		plane=plane6
	},

	{
		time=35.0,
		plane=plane1
	},
	{
		time=35.0,
		plane=plane2
	},
	{
		time=35.0,
		plane=plane3
	},
	{
		time=35.0,
		plane=plane4
	},
	{
		time=35.0,
		plane=plane5
	},
	{
		time=35.0,
		plane=plane6
	},


	{
		time=40.0,
		plane=plane1
	},

	{
		time=42.0,
		plane=plane2
	},
	{
		time=42.0,
		plane=plane3
	},

	{
		time=45.0,
		plane=plane1
	},
	{
		time=45.0,
		plane=plane2
	},
	{
		time=45.0,
		plane=plane3
	},

	{
		time=51.0,
		plane=plane1
	},
	{
		time=51.0,
		plane=plane2
	},
	{
		time=51.0,
		plane=plane3
	},
	{
		time=51.0,
		plane=plane4
	},

	{
		time=55.0,
		plane=plane1
	},
	{
		time=57.0,
		plane=plane1
	},
	{
		time=59.0,
		plane=plane1
	},
	{
		time=61.0,
		plane=plane1
	},
	{
		time=63.0,
		plane=plane1
	},
	{
		time=65.0,
		plane=plane1
	},









}


