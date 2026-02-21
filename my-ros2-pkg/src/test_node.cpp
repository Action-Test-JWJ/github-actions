#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class TestNode : public rclcpp::Node
{
public:
  TestNode() : Node("test_node"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("test_topic", 10);
    timer_ = this->create_wall_timer(
      std::chrono::seconds(1),
      std::bind(&TestNode::timer_callback, this));
    RCLCPP_INFO(this->get_logger(), "Test node started");
  }

private:
  void timer_callback()
  {
    auto msg = std_msgs::msg::String();
    msg.data = "Hello from test_node: " + std::to_string(count_++ *3);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", msg.data.c_str());
    publisher_->publish(msg);
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  int count_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TestNode>());
  rclcpp::shutdown();
  return 0;
}
