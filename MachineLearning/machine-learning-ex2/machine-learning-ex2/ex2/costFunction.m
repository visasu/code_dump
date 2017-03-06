function [J, grad] = costFunction(theta, X, y)
%COSTFUNCTION Compute cost and gradient for logistic regression
%   J = COSTFUNCTION(theta, X, y) computes the cost of using theta as the
%   parameter for logistic regression and the gradient of the cost
%   w.r.t. to the parameters.

% Initialize some useful values
m = length(y); % number of training examples

% You need to return the following variables correctly 
J = 0;
grad = zeros(size(theta));
size(theta)
h_theta=sigmoid(X*theta)
J=sum(-y.*log(h_theta)-(1-y).*log(1-h_theta))/m
D_J1=sum((h_theta-y).*X(:,1))/m
D_J2=sum((h_theta-y).*X(:,2))/m
D_J3=sum((h_theta-y).*X(:,3))/m
grad=[D_J1;D_J2;D_J3]
% ====================== YOUR CODE HERE ======================
% Instructions: Compute the cost of a particular choice of theta.
%               You should set J to the cost.
%               Compute the partial derivatives and set grad to the partial
%               derivatives of the cost w.r.t. each parameter in theta
%
% Note: grad should have the same dimensions as theta
%








% =============================================================

end
