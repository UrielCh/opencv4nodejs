export class TrackerCSRTParams {
  constructor();
  readonly admm_iterations: number;
  readonly background_ratio: number;
  readonly cheb_attenuation: number;
  readonly filter_lr: number;
  readonly gsl_sigma: number;
  readonly histogram_bins: number;
  readonly histogram_lr: number;
  readonly hog_clip: number;
  readonly hog_orientations: number;
  readonly kaiser_alpha: number;
  readonly num_hog_channels_used: number;
  readonly number_of_scales: number;
  readonly padding: number;
  // since openCV 3.4.4
  readonly psr_threshold?: number;
  readonly scale_lr: number;
  readonly scale_model_max_area: number;
  readonly scale_sigma_factor: number;
  readonly scale_step: number;
  readonly template_size: number;
  readonly use_channel_weights: boolean;
  readonly use_color_names: boolean;
  readonly use_gray: boolean;
  readonly use_hog: boolean;
  readonly use_rgb: boolean;
  readonly use_segmentation: boolean;
  readonly weights_lr: number;
  readonly window_function: string;
}
