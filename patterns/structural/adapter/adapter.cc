// Adapter pattern
// The adapter pattern (also wrapper) is used to connect an existing implementation (interface) to a new, not
//  compatible interface (library.
// Instead of creating new child classes, an adapter is created which transforms the input from one
//  side to the input for the other side and vice versa.
// The logic is separated from both implementations.
// There exists two adapters, one with inheritance from both interfaces, and one with composition which is more flexible.

// Client classes (existing code)

#include <cstdint>
#include <vector>
#include <memory>

struct Shape
{
  Shape() = default;
  virtual ~Shape() = default;
  virtual void Draw() = 0;
};

struct Rectangle : public Shape
{
  Rectangle() = default;
  void Draw() override
  {

  }
};

// Library (incompatible interface)
struct TextView
{
    TextView() = default;
    virtual ~TextView() = default;

    inline std::int32_t GetTopLeft() const
    {
      return top_left_;
    }

    inline std::int32_t GetBottomRight() const
    {
      return bottom_right_;
    }

  private:
    std::int32_t top_left_;
    std::int32_t bottom_right_;
};

// Composite Adapter

struct CompositeAdapter : public Shape
{
  CompositeAdapter(std::unique_ptr<TextView> text_view) : text_view_{std::move(text_view)} {}

  void Draw() override
  {
    text_view_->GetTopLeft();
    text_view_->GetBottomRight();
  }

private:
  std::unique_ptr<TextView> text_view_;
};

// Inheritance adapter

struct ShapeTextViewAdapter : public Shape, private TextView
{
  ShapeTextViewAdapter() = default;

  void Draw() override
  {
      GetTopLeft();
      GetBottomRight();
  }
};



int main()
{
    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(std::make_shared<Rectangle>());
    shapes.push_back(std::make_shared<ShapeTextViewAdapter>());
    shapes.push_back(std::make_shared<CompositeAdapter>(std::make_unique<TextView>()));

    for (const auto& shape : shapes)
    {
      shape->Draw();
    }
}
