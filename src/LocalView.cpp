#include "LocalView.h"

void LocalView::setCar(Car* c) {
	this->car = c;
}

void LocalView::setTrack(Track* t) {
	this->track = t;
}

void LocalView::setWindow(RenderWindow* w) {
	this->window = w;
}

void LocalView::setView(View* v) {
	this->view = v;
}

void LocalView::display() {
	view->setCenter(view->getCenter().x / 2 + car->GetPosX() / 2, view->getCenter().y / 2 + car->GetPosY() / 2);
	window->setView(*view);

	track->draw(*window);
	CircleShape circle(5);
	circle.setPosition(car->GetPosX(), car->GetPosY());
	window->draw(circle);

	window->display();
}