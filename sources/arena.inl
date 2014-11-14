//


Arena::Arena(int height, int width){
	this->shooter =  new Shooter();
	this->shooter->reload(0);
	this->height = height;
	this->width = width;
}
