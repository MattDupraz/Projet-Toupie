class NonRollingTop : public Top {
	// P = [psi, theta, phi]
	public:	
		NonRollingTop(std::shared_ptr<View> v, Vector const& A, 
				Vector const& P,	Vector const& DP,
				double m, double d, double I_1, double I_3)
			: Top(std::move(v), P, DP), A(A), m(m), d(d), I_1(I_1), I_3(I_3)
		{}

		// Retourne la seconde derivee
		virtual Vector getDDP(Vector P, Vector DP) override;	

		// Retourne les angles d'euler
		double psi() const override { return P_[0]; }
		double theta() const override { return P_[1]; }
		double phi() const override { return P_[2]; }

		// Retourne les coordonnees du point de contact
		double x() const override { return A[0]; }
		double y() const override { return A[1]; }
		double z() const override { return A[2]; }

		// Retourne les derivees des angles d'euler
		double d_psi() const { return DP_[0]; }
		double d_theta() const { return DP_[1]; }
		double d_phi() const { return DP_[2]; }

		// Retourne la distance du centre de masse du point de contact
		double getHeightCM() const { return d; }
		// Retourne la masee
		double getMass() const { return m; }

		// Retourne le vecteur position du point de contact
		Vector getOrigin() const { return A; }

		// Retourne l'énergie
		virtual double getEnergy()const override;
		// Retourne le moment cinétique en A
		virtual double getAngMomentumK() const override {return I_A3 * phi();}
		virtual double getAngMomentumA() const override;
	protected:	
		NonRollingTop(std::shared_ptr<View> v, Vector const& A,
				Vector const& P, Vector const& DP)
			: Top(std::move(v), P, DP), A(A)
		{}


		Vector A; // Contact point

		double m; // Mass
		double d; // Distance from contact point to center of mass
		// Moments of inertia with respect to A (point of contact)
		double I_A1; // Moment of inertia - horizontal axes
		double I_A3; // Moment of inertia - vertical axis
};