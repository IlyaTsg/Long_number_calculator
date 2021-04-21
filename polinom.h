#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

template <typename COEF>
long long intstr(std::string str, int i = 0)
{
	long long n = str.size(), sum = 0;
	for (; i < n && str[i] >= '0' && str[i] <= '9'; i++) sum = 10LL * sum + static_cast<long long>(str[i] - '0');
	return sum;
}

template <class IND, class COEF>
class polinom
{
private:
	std::vector<IND> ind;
	std::map<IND, COEF> coef;

public:
	polinom<IND, COEF>() {}
	polinom<IND, COEF>(COEF n) : ind({ 0 }) { coef[0] = n; }
	polinom<IND, COEF>(IND l, COEF n) : ind({ l }) { coef[l] = n; }
	polinom<IND, COEF>(std::vector<IND> Ind, std::map<IND, COEF> Coef) : ind(Ind), coef(Coef) {}
	polinom<IND, COEF>(std::vector<IND> Ind, std::vector<COEF> Coef) : ind(Ind) { for (int i = 0, n = Ind.size(); i < n; i++) coef[ind[i]] = Coef[i]; }
	//polinom<IND, COEF>(std::string pol)

	template <class IND, class COEF> friend polinom<IND, COEF> operator -(polinom<IND, COEF>&);
	template <class IND, class COEF> friend polinom<IND, COEF> operator +(polinom<IND, COEF>&, polinom<IND, COEF>&);
	template <class IND, class COEF> friend polinom<IND, COEF> operator -(polinom<IND, COEF>&, polinom<IND, COEF>&);
	template <class IND, class COEF> friend polinom<IND, COEF> operator *(polinom<IND, COEF>&, polinom<IND, COEF>&);
	template <class IND, class COEF> friend polinom<IND, COEF> operator /(polinom<IND, COEF>&, polinom<IND, COEF>&);
	template <class IND, class COEF> friend polinom<IND, COEF> operator %(polinom<IND, COEF>&, polinom<IND, COEF>&);
	/*std::ostream& operator>> (std::ostream& out, const polinom& val);
	vector< complex<T> > roots();
	complex<T> substitution(T val);
	polinom integral(T l_val, T r_val);
	friend polinom gcd(polinom l_val, polinom r_val);*/
	template <class IND, class COEF> friend polinom<IND, COEF> derivative(polinom<IND, COEF>& val);
	template <class IND, class COEF> friend polinom<IND, COEF> integral(polinom<IND, COEF>& val, COEF C);
	template <class IND, class COEF> friend std::ostream& operator<< (std::ostream&, polinom<IND, COEF>&);
};

template <typename IND>
std::vector<IND> merge(const std::vector<IND>& l_val, const std::vector<IND>& r_val)
{
	int a = l_val.size(), b = r_val.size();
	std::vector<IND> ans;
	for (int l = 0, r = 0; l < a || r < b;)
	{
		if (r == b || l < a && l_val[l] <= r_val[r])
		{
			if (r < b && l_val[l] == r_val[r]) r++;
			ans.push_back(l_val[l++]);
		}
		else ans.push_back(r_val[r++]);
	}
	return ans;
}


template <class IND, class COEF> 
polinom<IND, COEF> operator -(polinom<IND, COEF>& val)
{
	std::map<IND, COEF> new_coef;
	for (const auto& to : val.ind) new_coef[to] = -val.coef[to];
	return polinom<IND, COEF>(val.ind, new_coef);
}

template <typename IND, typename COEF>
polinom<IND, COEF> operator -(polinom<IND, COEF>& l_val, polinom<IND, COEF>& r_val)
{
	std::vector<IND> new_ind = merge(l_val.ind, r_val.ind);
	std::map<IND, COEF> new_coef;
	for (const auto& to : new_ind) new_coef[to] = l_val.coef[to] - r_val.coef[to];
	int l = 0;
	for (const auto& to : new_ind) if (new_coef[to] != 0) new_ind[l++] = to;
	new_ind.resize(l);
	return polinom<IND, COEF>(new_ind, new_coef);
}

template <typename IND, typename COEF>
polinom<IND, COEF> operator +(polinom<IND, COEF>& l_val, polinom<IND, COEF>& r_val)
{
	std::vector<IND> new_ind = merge(l_val.ind, r_val.ind);
	std::map<IND, COEF> new_coef;
	for (const auto& to : new_ind) new_coef[to] = l_val.coef[to] + r_val.coef[to];
	int l = 0;
	for (const auto& to : new_ind) if (new_coef[to] != 0) new_ind[l++] = to;
	new_ind.resize(l);
	return polinom<IND, COEF>(new_ind, new_coef);
}

template <typename IND, typename COEF>
std::ostream& operator<< (std::ostream& out, polinom<IND, COEF>& val)
{
	int n = val.ind.size();
	if (n == 0) out << 0;
	else for (int i = 0; i < n; i++)
	{
		IND to = val.ind[n - i - 1];
		if (i && val.coef[to] > 0) out << "+";
		if (val.coef[to] == -1) out << '-';
		else if (val.coef[to] != 1) out << val.coef[to];
		if (to > 0) out << 'x';
		if (to > 1)
		{
			out << "^" << to;
			if (i < n - 1) out << ' ';
		}
	}
	return out;
}

template <typename IND, typename COEF> 
polinom<IND, COEF> operator *(polinom<IND, COEF>& l_val, polinom<IND, COEF>& r_val)
{
	COEF comp = std::max(l_val.ind[l_val.ind.size() - 1], r_val.ind[r_val.ind.size() - 1]);
	if (1 || comp * sizeof(COEF) > static_cast<long long>(1 << 30))
	{
		std::vector<IND> new_ind;
		std::map<IND, COEF> new_coef;
		for (const auto& l : l_val.ind)
		{
			for (const auto& r : r_val.ind)
			{
				new_coef[l + r] = new_coef[l + r] + l_val.coef[l] * r_val.coef[r];
				new_ind.push_back(l + r);
			}
		}
		std::sort(new_ind.begin(), new_ind.end());
		int l = 1, n = new_ind.size();
		for (int i = 1; i < n; i++) if (new_ind[i] != new_ind[i - 1] && new_coef[new_ind[i]] != 0) new_ind[l++] = new_ind[i];
		new_ind.resize(l);
		return polinom<IND, COEF>(new_ind, new_coef);
	}
}

template <typename IND, typename COEF>
polinom<IND, COEF> operator /(polinom<IND, COEF>& l_val, polinom<IND, COEF>& r_val)
{
	std::vector<IND> new_ind;
	std::map<IND, COEF> new_coef;
	if (r_val.ind[r_val.ind.size() - 1] > l_val.ind[l_val.ind.size() - 1]) return polinom<IND, COEF>(new_ind, new_coef);
	polinom<IND, COEF> div(l_val);
	int r = r_val.ind[r_val.ind.size() - 1], l = div.ind[div.ind.size() - 1];
	while (r <= l)
	{
		new_ind.push_back(l - r);
		new_coef[l - r] = div.coef[l] / r_val.coef[r];
		polinom<IND, COEF> g(l - r, new_coef[l - r]);
		g = g * r_val;
		div = div - g;
		l = (div.ind.size() != 0 ? div.ind[div.ind.size() - 1] : -1);
	}
	for (int i = 0, n = new_ind.size(); i < n / 2; i++) std::swap(new_ind[i], new_ind[n - i - 1]);
	return polinom<IND, COEF>(new_ind, new_coef);
}

template <typename IND, typename COEF>
polinom<IND, COEF> derivative(polinom<IND, COEF>& val)
{
	std::vector<IND> new_ind;
	std::map<IND, COEF> new_coef;
	for (int i = (val.ind[0] == 0), n = val.ind.size(); i < n; i++)
	{
		new_ind.push_back(val.ind[i] - 1);
		new_coef[val.ind[i] - 1] = val.coef[val.ind[i]] * val.ind[i];
	}
	return polinom<IND, COEF>(new_ind, new_coef);
}


template <typename IND, typename COEF> 
polinom<IND, COEF> integral(polinom<IND, COEF>& val, COEF C)
{
	std::vector<IND> new_ind;
	std::map<IND, COEF> new_coef;
	if (C != 0)
	{
		new_ind.push_back(0);
		new_coef[0] = C;
	}
	for (int i = 0, n = val.ind.size(); i < n; i++)
	{
		new_ind.push_back(val.ind[i] + 1);
		new_coef[val.ind[i] + 1] = val.coef[val.ind[i]] / (val.ind[i] + 1);
	}
	return polinom<IND, COEF>(new_ind, new_coef);
}

template <typename IND, typename COEF> 
polinom<IND, COEF> operator %(polinom<IND, COEF>& l_val, polinom<IND, COEF>& r_val)
{
	polinom<IND, COEF> ans = l_val, help = l_val / r_val;
	help = help * r_val;
	ans = l_val - help;
	return ans;
}