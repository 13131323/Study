package com.example.pineapple.controller;

import com.example.pineapple.dto.RestaurantResponse;
import com.example.pineapple.repository.RestaurantRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@RequestMapping("/api/restaurants")
@RequiredArgsConstructor
public class RestaurantController {

    private final RestaurantRepository restaurantRepository;

    @GetMapping("/nearby")
    public List<RestaurantResponse> getNearbyRestaurants(
            @RequestParam double minLat,
            @RequestParam double maxLat,
            @RequestParam double minLng,
            @RequestParam double maxLng) {

        return restaurantRepository.findTop5InViewport(minLat, maxLat, minLng, maxLng)
                .stream()
                .map(RestaurantResponse::from)
                .toList();
    }
}