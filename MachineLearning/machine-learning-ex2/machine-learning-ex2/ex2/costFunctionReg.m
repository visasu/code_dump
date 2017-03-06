function [J, grad] = costFunctionReg(theta, X, y, lambda)
%COSTFUNCTIONREG Compute cost and gradient for logistic regression with regularization
%   J = COSTFUNCTIONREG(theta, X, y, lambda) computes the cost of using
%   theta as the parameter for regularized logistic regression and the
%   gradient of the cost w.r.t. to the parameters. 

% Initialize some useful values
m = length(y); % number of training examples

% You need to return the following variables correctly 
J = 0;
grad = zeros(size(theta));
J= zeros(size(theta));
k=size(theta);
K=0;
% ====================== YOUR CODE HERE ======================
% Instructions: Compute the cost of a particular choice of theta.
%               You should set J to the cost.
%               Compute the partial derivatives and set grad to the partial
%               derivatives of the cost w.r.t. each parameter in theta
h_theta=sigmoid(X*theta);
%J=sum(-y.*log(h_theta)-(1-y).*log(1-h_theta))/m %+ lambda*sum(theta(1).^2)/(2*m)
D_J1=sum((h_theta-y).*X(:,1))/m;
grad=D_J1;
for i=2:k
D_J1=sum((h_theta-y).*X(:,i))/m +lambda*theta(i)/m;
K=K+(theta(i).^2);
grad(i)=D_J1;
end
J=sum(-y.*log(h_theta)-(1-y).*log(1-h_theta))/m + lambda*K/(2*m);

% =============================================================

end
