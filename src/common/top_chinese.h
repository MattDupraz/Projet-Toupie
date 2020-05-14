class ChineseTop : public Top {
	// P = [psi, theta, phi, antiderivative of x, antiderivative of z]
	public:	
		ChineseTop(std::shared_ptr<View> v,
				Vector const& P,	Vector const& DP,
				double rho, double R, double h);

		// Retourne la seconde derivee
		virtual Vector getDDP(Vector P, Vector DP) override;	

		// Retourne les angles d'euler
		double psi() const override { return P_[0]; }
		double theta() const override { return P_[1]; }
		double phi() const override { return P_[2]; }

		// Retourne les coordonnees du centre de la sphere
		double x() const override { return DP_[3]; }
		double y() const override { return getRadius(); }
		double z() const override { return DP_[4]; }

		// Retourne les derivees des angles d'euler
		double d_psi() const { return DP_[0]; }
		double d_theta() const { return DP_[1]; }
		double d_phi() const { return DP_[2]; }
		// Retourne les dérivées des coordonnees des points de contacts
		double d_x() const { return DDP_cache[3]; }
		double d_z() const { return DDP_cache[4]; }

		// Retourne le rayon de la sphere
		double getRadius() const { return R; }
		// Retourne la masee
		double getMass() const { return m; }
		// Retourne la hauteur tronquée
		double getTruncatedHeight() const { return h; }
		// Retourne la masse volumique
		double getDensity() const { return rho; }
		// Retourne la hauteur du CM par rapport au centre de la sphere
		double getHeightCM() const { return - R * alpha; }

		// Methode necessaire pour le dessin (single dispatch)
		virtual void draw() const override {
			view_->draw(*this);
		}

		// Methode d'affichage
		virtual std::ostream& print(std::ostream& os) const override;

		virtual double getEnergy()const override;
		virtual double getAngMomentumK() const override { return I_3 * phi(); }
		virtual double getAngMomentumA() const override;
	protected:	
		double h; // truncated height
		double R; // sphere radius
		double rho; // density
		double m; // Mass
		double alpha; //Distance from center of mass from center of sphere
		// Moments of inertia with respect to A (point of contact)
		double I_1; // Moment of inertia - horizontal axes
		double I_3; // Moment of inertia - vertical axis

		// Saves DDP so we don't reevaluate when we need d_x and d_z
		Vector DDP_cache = Vector(std::size_t(5));

};
