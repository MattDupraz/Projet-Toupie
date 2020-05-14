#pragma once

class SimpleCone;
class ChineseTop;
class Gyroscope;
class GeneralTop;
class System;
class TopTest;

class View {
	public:
		virtual ~View() {}
		// Methodes pour dessiner les objets dessinables concrets
		virtual void draw(SimpleCone const& top) = 0;
		virtual void draw(Gyroscope const& top) = 0;
		virtual void draw(GeneralTop const& top) = 0;		
		virtual void draw(ChineseTop const& top) = 0;
		virtual void draw(System const& system) = 0;
};
