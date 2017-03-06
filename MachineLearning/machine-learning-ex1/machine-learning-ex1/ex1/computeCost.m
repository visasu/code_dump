function J = computeCost(X, y, theta)
%COMPUTECOST Compute cost for linear regression
%   J = COMPUTECOST(X, y, theta) computes the cost of using theta as the
%   parameter for linear regression to fit the data points in X and y

% Initialize some useful values
m = length(y); % number of training examples

% You need to return the following variables correctly 
J = 0;

% ====================== YOUR CODE HERE ======================
% Instructions: Compute the cost of a particular choice of theta
%               You should set J to the cost.

s_t=size(theta);
s_x=size(X);
s_y=size(y);
h_theta=X*theta;
s_theta=size(h_theta);
D1=(h_theta-y);    
D2=(h_theta-y);
J1=sum(D1.^2)/(2*m);
J2=sum(D2.^2)/(2*m);
J=J1;






% =========================================================================

end
