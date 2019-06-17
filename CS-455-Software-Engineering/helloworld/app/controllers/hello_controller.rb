class HelloController < ApplicationController
  def index
	@title = "My second Rails app!"   
	@count = 5   
	@line = "Text from the controller"
  end
end
