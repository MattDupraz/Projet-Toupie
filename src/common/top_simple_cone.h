class SimpleCone : public NonRollingTop {
	public:
		// rho = masse volumique
		// L = hauteur 
		// R = rayon a la base
		SimpleCone(std::shared_ptr<View> v, Vector const& A,
				Vector const& P, Vector const& DP,
				double rho, double L, double R);

		// Methode necessaire pour le dessin (single dispatch)
		virtual void draw() const override {
			view_->draw(*this);
		}
		
		// Accesseurs aux parametres du cone
		double getDensity() const { return rho; }
		double getHeight() const { return L; }
		double getRadius() const { return R; }

		// Methode d'affichage
		virtual std::ostream& print(std::ostream& os) const override;
	private:
		double rho; // Densite volumique du cone
		double L; // Hauteur du cone
		double R; // Rayon de la base
};
