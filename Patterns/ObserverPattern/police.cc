#include <iostream>

#include "police.h"
#include "subject.h"

Police::Police(Subject* subject) :
	subject_(subject)
{
	std::cout << " Police::Police() register subject" << std::endl;
	subject_->Register(this);
}

Police::~Police()
{
	std::cout << " Police::~Police() unregister subject" << std::endl;
	subject_->Unregister(this);
}

void Police::Update(Subject* subject)
{
	if(subject == subject_)
	{
		std::cout << " Police::Update() for subject called" << std::endl;
	}
}
