class Gyroscope : public NonRollingTop {
	public:
		Gyroscope(std::shared_ptr<View> v, Vector const& A,
				Vector const& P, Vector const& DP,
				double d, double rho, double L, double R);

		// Methode necessaire pour le dessin (single dispatch)
		virtual void draw() const override {
			view_->draw(*this);
		}

		// Accesseurs aux variables du gyroscope
		double getDensity() const { return rho; }
		double getThickness() const { return L; }
		double getRadius() const { return R; }
		double getHeight() const { return d; }

		// Methode d'affichage
		virtual std::ostream& print(std::ostream& os) const override;
	private:
		double rho; // Densite volumique de disque
		double L; // Largeur du disque
		double R; // Rayon du disque
};
