function [theta, J_history] = gradientDescent(X, y, theta, alpha, num_iters)
%GRADIENTDESCENT Performs gradient descent to learn theta
%   theta = GRADIENTDESENT(X, y, theta, alpha, num_iters) updates theta by 
%   taking num_iters gradient steps with learning rate alpha

% Initialize some useful values
%num_iters=15000;
m = length(y); % number of training examples
J_history = zeros(num_iters, 1);

for iter = 1:num_iters

    % ====================== YOUR CODE HERE ======================
    % Instructions: Perform a single gradient step on the parameter vector
    %               theta. 
    %
    % Hint: While debugging, it can be useful to print out the values
    %       of the cost function (computeCost) and gradient here.
    %
    
    s_t=size(theta);
    s_x=size(X);
    s_y=size(y);
    h_theta=X*theta;
    s_theta=size(h_theta);
    D1=(h_theta-y).*X(:,1);    
    D2=(h_theta-y).*X(:,2);
    J11=sum(D1)/m;
    J22=sum(D2)/m;
    theta(1)=theta(1)-alpha*J11;
    theta(2)=theta(2)-alpha*J22;

    % ============================================================

    % Save the cost J in every iteration    
    J_history(iter) = computeCost(X, y, theta);

end

end
