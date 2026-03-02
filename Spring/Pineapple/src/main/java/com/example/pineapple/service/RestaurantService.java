package com.example.pineapple.service;

import com.example.pineapple.entity.Restaurant;
import com.example.pineapple.repository.RestaurantRepository;
import jakarta.persistence.Table;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
@Transactional(readOnly = true)
@RequiredArgsConstructor
public class RestaurantService {
    private final RestaurantRepository restaurantRepository;

    // 모든 식당 정보를 조회하여 지도에 표시할 데이터를 제공

    public List<Restaurant> findAllRestaurants() {
        return restaurantRepository.findAll();
    }
}
