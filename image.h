#ifndef IMAGE_H
#define IMAGE_H

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T> class Image {
public:
    // Construct an image given width and height
    Image(std::size_t width = 0, std::size_t height = 0);

    // get the width of the image
    std::size_t width() const;

    // get the height of the image
    std::size_t height() const;

    T& operator()(std::size_t i, std::size_t j);

    T operator()(std::size_t i, std::size_t j) const;

private:
    std::size_t _width, _height;
    std::vector<T> _data;
};

struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

// equality comparisons for Pixel
bool operator==(const Pixel& a, const Pixel& b);
bool operator!=(const Pixel& a, const Pixel& b);

// read an Image of RGBA pixels from the PNG
Image<Pixel> readFromFile(std::string fname);

// write an Image of RGBA pixels from the PNG
void writeToFile(const Image<Pixel>& im, std::string fname);

template <typename T>
Image<T>::Image(std::size_t width, std::size_t height)
    : _width(width), _height(height) {

    _data.resize(_width * _height);
}

template <typename T> std::size_t Image<T>::width() const { return _width; }

template <typename T> std::size_t Image<T>::height() const { return _height; }

template <typename T> T& Image<T>::operator()(std::size_t i, std::size_t j) {

    if ((j >= _height) || (i >= _width))
        throw std::out_of_range("Image: Invalid location in operator()");

    return _data[j * _width + i];
}

template <typename T>
T Image<T>::operator()(std::size_t i, std::size_t j) const {

    if ((j >= _height) || (i >= _width))
        throw std::out_of_range("Image: Invalid location in operator()");

    return _data[j * _width + i];
}

#endif // IMAGE_H
