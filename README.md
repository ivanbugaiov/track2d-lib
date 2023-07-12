# track2d-lib

track2d-lib is a c++ library for estimating trajectory on a 2d plane

## Installation

Clone the project and build it with a standard `cmake` and `make` routine:

```bash
git clone https://github.com/ivanbugaiov/track2d-lib
cd track2d-lib
mkdir -p build
cd build
cmake ..
make
```

## Preparatory work

This is a shared library meant to be used as a dependency.

Moreover, user application has to provide implementation for `PlotSource` and `Perimeter` types. 

`PlotSource` type declaration:

```cpp
class IPlotSource {
public:
    virtual ~IPlotSource() {}
    virtual std::optional<Plot> get() = 0;
    virtual bool advance() = 0;
}; // IPlotSource
```
`PlotSource` handles feeding track data to estimator - be it from file, user input or over the net. 

`Perimeter` type declaration:

```cpp
class IPerimeter {
public:
    virtual bool is_point_inside(const Vector2D& pt) = 0;
}; // IPerimeter
```

`Perimeter` represents a region of interest for which estimator can produce a guess of whether the track will intercept it or not. Perimeter shape is totally user-defined, the only requirement is being able to answer if the point is inside the perimeter via the `is_point_inside` implementation.

## Usage

Once preparatory work is done, `TrackEstimator` is ready to be used. 

User application is responsible for controlling both the flow rate of new plot samples and their consumption by track estimator. Thus, a simplified workflow is as follows:
```cpp
// advancing plot source means that next plot is made available 
plot_source->advance(); 

// all estimators which share plot_source must advance in between plot_source->advance() calls
first_estimator->advance();
second_estimator->advance();
...
nth_estimator->advance();

// next plot is made available 
plot_source->advance(); 

// the cycle repeats
first_estimator->advance();
second_estimator->advance();
...
nth_estimator->advance();
```

Users are free to implement whatever scheduling and synchronization scheme fits their application best. When plot data is read from file, a simple loop will suffice. In cases when plot data is arriving in real time, busy loops or fd polling will likely appear to be more practical.

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[MIT](https://choosealicense.com/licenses/mit/)
